<?php
// $host = 'localhost';
$host = 'mysql762.umbler.com';
$user = 'devbovino';
$pass = '123456789a';
$db   = 'devbovino';
// conecta com o banco de dados
$con = mysqli_connect($host, $user, $pass,$db);
// efetua a consulta

    $sql = "INSERT INTO gados (id_gado) VALUES (". $_GET['id_gado'] .")";
    mysqli_query($con,$sql);


// fecha a conexão
mysqli_close($con);