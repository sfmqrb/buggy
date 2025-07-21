<?php
require 'utils.php';
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $host = $_POST['host'] ?? '';
    // Command Injection: unsanitized host
    $output = shell_exec("ping -c 1 $host 2>&1");
}
?>
<h2>Ping Tool</h2>
<form method="POST">
  Host: <input name="host" placeholder="127.0.0.1">
  <button type="submit">Ping</button>
</form>
<pre><?= $output ?? '' ?></pre>
