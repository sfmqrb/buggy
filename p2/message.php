<?php
require 'utils.php';
require_login();
require 'db.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $db = get_db();
    $uid = current_user()['id'];
    $stmt = $db->prepare("INSERT INTO messages(user_id, content) VALUES (?, ?)");
    $stmt->execute([$uid, $_POST['content']]);
    header("Location: index.php");
    exit;
}
?>
<h2>Post Message</h2>
<form method="POST">
  <textarea name="content" rows="4" cols="40"></textarea><br>
  <button type="submit">Post</button>
</form>
