<?php require 'utils.php'; require 'db.php'; ?>
<!DOCTYPE html>
<html>
<head><title>VulnApp</title></head>
<body>
<h1>VulnApp</h1>
<?php if (current_user()): ?>
<p>Hello, <?= current_user()['username'] ?> |
   <a href="logout.php">Logout</a></p>
<p><a href="message.php">Post Message</a> |
   <a href="search.php">Search</a> |
   <a href="ping.php">Ping Tool</a></p>
<?php else: ?>
<p><a href="login.php">Login</a> or <a href="register.php">Register</a></p>
<?php endif; ?>

<h2>Recent Messages (Stored XSS)</h2>
<?php
$db = get_db();
$res = $db->query("SELECT messages.id, content, username FROM messages JOIN users ON users.id = messages.user_id ORDER BY messages.id DESC LIMIT 10;");
foreach ($res as $row) {
    // No escaping: Stored XSS
    echo "<div><strong>{$row['username']}:</strong> {$row['content']}</div>";
}
?>
</body>
</html>
