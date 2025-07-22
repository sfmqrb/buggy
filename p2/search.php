<?php require 'utils.php'; require_login(); require 'db.php'; $q=$_GET['q']??''; site_header('Search Users'); ?>
<h2>Search Users <small style="font-size:.6em; color:#999;">(SQLi + Reflected XSS)</small></h2>
<form>
  <input name="q" value="<?= $q ?>" placeholder="search username"> <button type="submit">Search</button>
</form>
<?php if($q!==''){ echo "<p>Results for: $q</p>"; $db=get_db(); $sql="SELECT id, username FROM users WHERE username LIKE '%$q%'"; foreach($db->query($sql) as $row){ echo "<div><a href='user.php?id={$row['id']}'>".$row['username']."</a></div>"; } } site_footer(); ?>

