_The AstraNav probe is set to launch to chart methane plumes on Titan, but its core software stack is a relic: a 25‑year‑old C/C++ navigation binary bolted to a PHP/SQLite “mission console” hastily built during a funding sprint. A single crash or forged packet mid‑flight could waste fuel or disable critical systems, so Command assigns you to harden both layers in the narrow window before rollout._

_First, you tackle the flight binary. Using coverage‑guided fuzzing, you provoke crashes, capture minimal reproducible inputs, and patch at least six memory issues—while keeping the command interface unchanged so existing scripts still function during Titan orbit insertion._

_Next, you audit the PHP console used by ground crew to upload maneuvers and read telemetry. It freely concatenates user input into SQL, reflects it in HTML, and even shells out to ping subsystems. You document six distinct exploits showing how each could misalign antennas or leak scientific data, then propose precise fixes to ensure the console communicates only with trusted operators once AstraNav is coasting beyond Saturn._


## Problem 1: Finding bugs in our memory-unsafe C/C++ binary

The program parses user commands into fixed-size buffers and uses unchecked string operations. Your task is to **find, trigger, and patch every memory-safety bug** (e.g., stack/heap overflows, UAFs, double frees, format strings) without altering observable behavior. Document all changes.

### Goals

* Identify each unsafe behavior.
* Produce a minimal crashing input (or script) for each issue.
* **Patch at least six bugs** while preserving functionality.

### Setup & Run

```bash
make
```

### Deliverables

* Patched source.
* Crashing inputs (pre-patch) for each bug.
* Fuzzing harness/tests, if used.
* A write-up: bug, trigger, root cause, and fix.

## Problem 2: Auditing and Exploiting a Vulnerable Web Application

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
   ```

4. **Deliverables**

* Patched source.
* Crashing inputs (pre-patch) for each bug.
* A write-up: bug, trigger, root cause, and fix.
   
---

> **Reminder:** Your objective is to *analyze*, *exploit*, and *document*. Focus on clarity and technical accuracy in your reports.


