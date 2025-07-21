<?php
require 'utils.php';
require 'db.php';
// IDOR: Any logged-out user can view arbitrary user records
$id = $_GET['id'] ?? '1';
$db = get_db();
$row = $db->query("SELECT * FROM users WHERE id = $id")->fetch(PDO::FETCH_ASSOC);
if (!$row) { echo "No such user"; exit; }
?>
<h2>User Profile</h2>
<p>ID: <?= $row['id'] ?></p>
<p>Username: <?= $row['username'] ?></p>
<p>Password (plaintext): <?= $row['password'] ?></p>
<a href="index.php">Back</a>
