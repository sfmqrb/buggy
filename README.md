# KVStore Bug‐Hunting Challenge

This repository contains a tiny C++ key‐value store library riddled with a plenty of intentional bugs. The main code lives in `kvstore.hpp` and `kvstore.cpp`, where methods like `put`, `get`, `remove`, `exists` and `clear` all carry subtle defects. A simple test harness (`run_kvstore.cpp`) exercises these operations, and a Dockerfile builds the project in Ubuntu and runs the KV store.

To get started, clone this repo and run `docker build -t kvbuggy .` followed by `docker run --rm kvbuggy`. You’ll immediately see crashes, thrown exceptions or failed assertions. That’s exactly the point: these failures point to the bugs you need to find.

Your task is to point a fuzzer (AFL, libFuzzer, honggfuzz or your own harness) at the test binary or write a custom driver that sends random keys, values and command sequences. When the program crashes or misbehaves, note the crash location and trace it back. Once you understand the root cause, correct the code, rebuild and rerun the fuzzer until that issue no longer appears.

When you’ve triaged and fixed each defect, prepare a branch or patch series where every commit clearly names the bug it addresses (for example, “fix: initialize capacity before allocation”). Push your changes and make sure to add logs from your fuzzer. This narrative approach will guide you through fuzzing, diagnosing, and repairing the buggy KVStore. Happy fuzzing!  
