**Problem 1: Finding bugs in our memory-unsafe C/C++ binary**

We wrote a deliberately vulnerable program that parses user commands into fixed-size buffers and performs unchecked string operations. Your job is to **find, trigger, and patch every memory-safety bug** (stack/heap overflows, UAFs, etc.) without changing the program’s intended behavior. At the end report all of these changes.


### Goals

* Locate each divergence from safe behavior (buffer overflow, format string, UAF, double free, etc.).
* Produce a minimal crashing input (or script) for each.
* **Patch at least 6 of them** and keep functionality the same.

### Why fuzzing?

Handwritten tests miss boundary cases. Coverage-guided fuzzers generate inputs that quickly expose overflows, empty/huge payloads, and nested cases.

### Setup & run

```bash
make            # normal build
```

### Deliverables

* A **patched source** that passes under sanitizers.
* **Crashing inputs** (before patch) demonstrating each bug.
* **Fuzzing harness/tests** if you used fuzzing.
* A **write-up** listing each bug, trigger, root cause, and fix.

That’s it—keep it tight. Let me know if you want Problem 2.

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


