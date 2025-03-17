#!/bin/bash

# Configuration
MINI_PROMPT="shell"
KO_COUNT=0
MINISHELL=./minishell
BASH_OUTPUT=bash_output.txt
MINISHELL_OUTPUT=minishell_output.txt
DIFF_OUTPUT=diff_output.txt

# List of commands to test, organized by category
declare -A commands=(
    ["Simple Commands"]="
        /bin/ls
        \n
        ' '
        /bin/ls -l
        /bin/echo Hello World
        /bin/cat file.txt
    "
    ["echo"]="
        echo
        echo Hello World
        echo -n Hello World
        echo \"Hello   World\"
        echo \"cat file.txt | grep something\"
        echo '$USER'
        echo 'Hello   World'
        echo teste\"     \"teste
        echo teste\"''\"'\"\"'teste
    "
    ["exit"]="
        exit
        exit 42
    "
    ["Return Value"]="
        /bin/ls
        echo $?
        /bin/ls nonexistentfile
        echo $?
        expr $? + $?
    "
    ["Double Quotes"]="
        echo \"Hello   World\"
        echo \"cat file.txt | grep something\"
    "
    ["Single Quotes"]="
        echo '$USER'
        echo 'Hello   World'
    "
    ["env"]="
        env
    "
    ["export"]="
        export MY_VAR=Hello
        env | grep MY_VAR
        export PATH=/new/path
        env | grep PATH
    "
    ["unset"]="
        unset MY_VAR
        env | grep MY_VAR
    "
    ["cd"]="
        cd /tmp
        pwd
        cd ..
        pwd
    "
    ["pwd"]="
        pwd
    "
    ["Relative Path"]="
        cat ./Makefile
        cat ./src/minishell_main.c
    "
    ["Environment Path"]="
        ls
        unset PATH
        ls
        export PATH=/bin:/usr/bin
        ls
    "
    ["Redirection"]="
        cat < Makefile
        echo Hello > output.txt
        cat <output.txt
        rm output.txt
        echo World >> output.txt
        cat <output.txt
        rm output.txt
    "
    ["Pipes"]="
        cat Makefile | grep minishell | wc -l
        cat Makefile | grep minishell > output.txt
    "
)
# comp
make
# Function to run tests for a category
run_tests_for_category() {
    local category="$1"
    local commands_list="$2"

    echo -e "\n\033[1;34m=== Testing $category ===\033[0m"

    while IFS= read -r cmd; do
        if [ -z "$cmd" ]; then
            continue
        fi

        echo -e "\nTesting: $cmd"

        # Run command in bash
        echo -e "$cmd" | bash > "$BASH_OUTPUT" 2>&1

        # Run command in minishell
        echo -e "$cmd" | $MINISHELL | grep -v "$MINI_PROMPT" > "$MINISHELL_OUTPUT" 2>&1

        # Compare outputs
        diff "$BASH_OUTPUT" "$MINISHELL_OUTPUT" > "$DIFF_OUTPUT"

        if [ -s "$DIFF_OUTPUT" ]; then
            echo -e "\033[31mKO: \033[0m" "$cmd"
            echo "Bash output:"
            cat "$BASH_OUTPUT"
            echo "Minishell output:"
            cat "$MINISHELL_OUTPUT"
            ((KO_COUNT++))
        else
            echo -e "\033[32mOK\033[0m"
        fi
    done <<< "$commands_list"
}

# Function to run all tests
run_tests() {      cat ./src/minishell_main.c
    "
    ["Environment Path"]="
        ls
    echo "Starting minishell tests..."

    for category in "${!commands[@]}"; do
        run_tests_for_category "$category" "${commands[$category]}"
    done

    # Cleanup
    rm -f "$BASH_OUTPUT" "$MINISHELL_OUTPUT" "$DIFF_OUTPUT"

    # Print results
    echo -e "\n\033[1;34m=== Testing Complete ===\033[0m"
    echo "You got $KO_COUNT KO's."
}


# Run the tests
run_tests
