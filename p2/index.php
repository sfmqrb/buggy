<?php require 'utils.php'; require 'db.php'; site_header(); ?>
<h2>Recent Messages <small style="font-size:.6em; color:#999;">(Stored XSS)</small></h2>
<p>Welcome to the deliberately vulnerable app. Try all the classic attacks.</p>
<?php
$db = get_db();
$res = $db->query("SELECT messages.id, content, username FROM messages JOIN users ON users.id = messages.user_id ORDER BY messages.id DESC LIMIT 10;");
foreach ($res as $row) {
    echo "<div class='message'><span class='user-tag'>".$row['username']."</span> ".$row['content']."</div>"; // no escaping
}
?>
<?php site_footer(); ?>
