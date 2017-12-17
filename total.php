<?php
// $host = 'localhost';
$host = 'mysql762.umbler.com';
$user = 'devbovino';
$pass = '123456789a';
$db   = 'devbovino';
// conecta com o banco de dados
$con = mysqli_connect($host, $user, $pass,$db);
// efetua a consulta

    $sql = "SELECT COUNT(*) FROM gados AS total";
    $query = mysqli_query($con,$sql);
    $res = mysqli_fetch_array($query);
    
    echo("
    
    TOTAL DE GADO: ". $res[0]."

    ");


// fecha a conexão
mysqli_close($con);