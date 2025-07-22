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

Link to the official MessagePack library (for reference and testing):
```bash
pip install msgpack
```

You can then import it in Python as:

```python
import msgpack
```

> **Note:** the bugs are in *our* implementation (`msgpacker.py`), not in the official library. Use the official `msgpack` purely as a correctness oracle.


**Problem 2: Auditing and Exploiting a Vulnerable Web Application**

You are given a deliberately insecure PHP/SQLite web application packaged as a Docker image. Your task is to investigate the code and runtime behavior, discover **at least six distinct vulnerabilities**, exploit them, and document each with a proposed fix.

Our starter materials provide:

* **Application source** (`.php` files) and an auto-initialized **SQLite database** (`data.db`).
* A **Dockerfile** you can build locally to run the app.

---

1. **What’s happening here?**
   The container launches an Apache/PHP server that exposes multiple dynamic endpoints (login, registration, message posting, search, user profiles, a ping tool, etc.). The code intentionally omits common safeguards (input validation, output encoding, access control), creating an environment suitable for security analysis.

2. **Your goals**

   * Find **six different vulnerabilities** in the codebase (e.g., injection, XSS, insecure direct object reference, command execution, weak authentication logic, etc.). Do **not** reuse the same root cause twice.
   * For each vulnerability, produce an exploit demonstrating impact.
   * For each, propose a concrete fix (code change or mitigation strategy).

3. **Setup and running the application**

   Build and run the Docker image:

   ```bash
   docker build -t vuln-app .
   docker run -d -p 9090:80 vuln-app
   ```

   Visit the application in your browser at:

   ```
   http://localhost:9090/
   ```

   To inspect code and database from inside the container:

   ```bash
   docker ps                     # find container ID
   docker exec -it <id> bash
   cd /var/www/html
   sqlite3 data.db
   ```

4. **Deliverables**
   Submit a report (Markdown or PDF) containing **six vulnerability entries**. For each entry include:

   * **Title:** short name of the issue.
   * **Location:** filename and function/line reference.
   * **Description:** what is wrong and why it is a vulnerability.
   * **Reproduction / Exploit:** exact steps or payload used.
   * **Impact:** what an attacker gains (e.g., data disclosure, code execution).
   * **Fix:** precise remediation (e.g., parameterized queries, escaping, access control, input validation, least privilege).

   Do not modify the application while discovering issues; fixes should be described, not applied (unless you create a patched version separately).

---

> **Reminder:** Your objective is to *analyze*, *exploit*, and *document*. Focus on clarity and technical accuracy in your reports.


