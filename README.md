**Problem 1: Finding bugs in our MessagePack implementation**

We have written a buggy library that implements the MessagePack encoding format. MessagePack is a binary serialization format similar in spirit to JSON: it supports integers, booleans, strings, arrays (lists/tuples), and maps (dictionaries) without requiring a pre-defined schema. Your task is to find and fix all bugs in our implementation.

Our starter code provides:

* **`msgpacker.py`** — the (buggy) encoder/decoder you must correct.
* **`msgpacker_example.py`** — a small script demonstrating intended usage:

```bash
% python msgpacker_example.py
example: {'Hello': 'world',
          'foo': ('bar', 'baz', 'quux'),
          'flag': True,
          'count': 123}
encoding: b'\x84\xa5Hello\xa5world\xa3foo\x93\xa3bar\xa3baz\xa4quux\xa4flag\xc2\xa5count{'
example2: {'Hello': 'world',
           'foo': ('bar', 'baz', 'quux'),
           'flag': True,
           'count': 123}
```

1. **What’s happening here?**

   * Line 1: we construct a nested Python structure (dict of tuple, bool, int, str).
   * Line 2: we print its MessagePack encoding bytes.
   * Line 3: we decode those bytes back into a Python object (`example2`), which should exactly match the original.

2. **Your goals**

   * Locate and fix every divergence between our encoder/decoder and the [official MessagePack spec](https://github.com/msgpack/msgpack/blob/master/spec.md).
   * You may omit support for floating-point numbers (as in our starter code).
   * Use the standard Python [`msgpack`](https://pypi.org/project/msgpack/) library as a golden reference to validate your fixes.

3. **Why fuzzing?**

   * Relying on hand-written test cases can easily miss corner cases (e.g. very large integers, empty maps, nested structures, unicode strings, boundary lengths, etc.).
   * You can include [Atheris](https://pypi.org/project/atheris/) to automatically generate inputs that expose bugs in `msgpacker.py`.

4. **Setup and running the fuzzer**

   ```bash
   % make
   python3 -m venv venv
   venv/bin/pip install -r requirements.txt || ( rm -r venv; false )
   ```

5. **Deliverables**

   * A **corrected `msgpacker.py`** that fully conforms to MessagePack (except for floats).
   * Any **fuzzing harness or test scripts** you wrote to uncover and demonstrate each bug.
   * (Optional) A brief write-up listing the bugs you discovered and how you fixed them.

---

**Link to the official MessagePack library (for reference and testing):**

```bash
pip install msgpack
```

You can then import it in Python as:

```python
import msgpack
```

> **Note:** the bugs are in *our* implementation (`msgpacker.py`), not in the official library. Use the official `msgpack` purely as a correctness oracle.
