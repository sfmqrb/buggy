<?php
require 'utils.php';
require 'db.php';
$q = $_GET['q'] ?? '';
?>
<h2>Search Users</h2>
<form>
  <input name="q" value="<?= $q ?>">
  <button type="submit">Search</button>
</form>
<?php
if ($q !== '') {
    // Reflected XSS: echo $q
    echo "<p>Results for: $q</p>";
    $db = get_db();
    // SQL Injection
    $sql = "SELECT id, username FROM users WHERE username LIKE '%$q%'";
    foreach ($db->query($sql) as $row) {
        echo "<div><a href='user.php?id={$row['id']}'>".$row['username']."</a></div>";
    }
}
