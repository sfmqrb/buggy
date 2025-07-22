<?php require 'utils.php'; require 'db.php'; $id=$_GET['id']??'1'; $db=get_db(); $row=$db->query("SELECT * FROM users WHERE id = $id")->fetch(PDO::FETCH_ASSOC); if(!$row){ echo 'No such user'; exit; } site_header('User Profile'); ?>
<h2>User Profile <small style="font-size:.6em; color:#999;">(IDOR + Plaintext Password)</small></h2>
<p><strong>ID:</strong> <?= $row['id'] ?></p>
<p><strong>Username:</strong> <?= $row['username'] ?></p>
<p><strong>Password:</strong> <?= $row['password'] ?></p>
<p><a href="index.php">Back</a></p>
<?php site_footer(); ?>

