<?php
	try {
		$bdd = new PDO('mysql:host=localhost;dbname=fuxpl152_fux', 'fuxpl152', '8T31v}hT;%(T');/*nom de la base, login, mdp*/
		//$bdd = new PDO('mysql:host=localhost;dbname=fu(x)', 'root', '');/*nom de la base, login, mdp*/
	} catch(Exception $e)
	{ die('Erreur : '.$e->getMessage());}
?>