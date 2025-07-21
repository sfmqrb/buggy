<?php
require 'utils.php';
require 'db.php';

$error = null;

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $db = get_db();
    $sql = "SELECT * FROM users WHERE username = '{$_POST['username']}' AND password = '{$_POST['password']}' LIMIT 1;";
    $row = $db->query($sql)->fetch(PDO::FETCH_ASSOC);
    if ($row) {
        $_SESSION['user'] = $row;
        header("Location: index.php");
        exit;
    } else {
        $error = "Invalid credentials";
    }
}
?>

<h2>Login</h2>
<?php if (!empty($error)) echo "<p>$error</p>"; ?>
<form method="POST">
  Username: <input name="username"><br>
  Password: <input name="password" type="password"><br>
  <button type="submit">Login</button>
</form>

