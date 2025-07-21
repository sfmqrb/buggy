<?php
require 'utils.php';
require 'db.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $db = get_db();
    // Weak password storage (plaintext)
    $sql = "INSERT INTO users(username,password) VALUES ('{$_POST['username']}', '{$_POST['password']}')";
    try {
        $db->exec($sql); // SQL injection possible via username
        echo "Registered! <a href='login.php'>Login</a>";
        exit;
    } catch (Exception $e) {
        echo "Error: " . htmlspecialchars($e->getMessage());
    }
}
?>
<form method="POST">
  <h2>Register</h2>
  Username: <input name="username"><br>
  Password: <input name="password" type="password"><br>
  <button type="submit">Register</button>
</form>
