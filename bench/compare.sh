#!/bin/bash

tests=$(ls *.scm)

header() {
    echo
    echo "=============================================="
    echo "Testing $1"
    echo "=============================================="
}

# ---------- RVM BUILD ----------
build_rvm() {
    echo "== Building RVM =="
    pushd ../src/host/c > /dev/null

    make clean > /dev/null 2>&1
    make > /dev/null 2>&1

    cp rvm ../../../bench/rvm
    cp rvm3 ../../../bench/rvm3

    popd > /dev/null
    echo "== RVM READY =="
}

# ---------- GENERIC RUN ----------
run() {
    exe="$1"
    header "$exe"

    benches=()

    for test in $tests
    do
        if [[ -f "./$exe" ]]; then
            benches+=("cat $test | ./$exe")
        else
            benches+=("cat $test | $exe")
        fi
    done

    for cmd in "${benches[@]}"; do
        echo "----------------------"
        echo "Running: $cmd"
        time bash -c "$cmd"
    done
}

# ---------- RVM LANGUAGE RUN ----------
runrvm() {
    lang="$1"
    exe="rvm-$lang"

    header "$exe"

    benches=()

    for test in $tests
    do
        filename="${test%.*}"
        cp "$test" ../src/"$test"

        pushd ../src > /dev/null

        out_file="$filename.scm.$lang"

        # Compile Scheme → target language
        gsi ./rsc.scm -l r4rs -t "$lang" "$test" -o "$out_file"

        # C compile
        if [[ "$lang" == "c" ]]; then
            gcc -o "$filename.c.exe" "$out_file"
            out_file="$filename.c.exe"
        fi

        popd > /dev/null

        if [[ "$lang" == "py" ]]; then
            benches+=("pypy3 ../src/$out_file")
        elif [[ "$lang" == "js" ]]; then
            benches+=("node ../src/$out_file")
        else
            benches+=("../src/$out_file")
        fi
    done

    for cmd in "${benches[@]}"; do
        echo "----------------------"
        echo "Running: $cmd"
        time bash -c "$cmd"
    done
}

# ---------- MAIN ----------

echo "== Preparing =="
build_rvm

echo "== Running Benchmarks =="

# C version (fastest)
runrvm c

# Python version
runrvm py

# JS version
runrvm js

echo "== DONE =="