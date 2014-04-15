<?php session_start(); ?>
<?php
	require("bdd.php");
	//if (isset($_POST['pseudo']) && isset($_POST['mdp']) && isset($_POST['commentaire']) && !empty($_POST['commentaire']))
	if (isset($_SESSION['pseudo']) && isset($_SESSION['mdp']) && isset($_POST['commentaire']) && !empty($_POST['commentaire']))
	{
		//$pseudo = htmlentities($_POST['pseudo'], ENT_QUOTES, 'UTF-8');
		//$mdp = htmlentities($_POST['mdp'], ENT_QUOTES, 'UTF-8');
		$message = nl2br(htmlentities($_POST['commentaire'], ENT_QUOTES, 'UTF-8'));
		$num_news = intval($_POST['num_news']);
		
		//$resultat = $bdd->query('SELECT * FROM utilisateur WHERE pseudo="'.$pseudo.'"');
		//$ligne = $resultat->fetch();
		
		/*if (strcmp($ligne['mdp'], $mdp) == 0)
		{
			$_SESSION['pseudo'] = $pseudo;
			$_SESSION['mdp'] = $mdp;
			$requete = 'INSERT INTO commentaire(num_news, pseudo, date, texte) VALUES (\''.$num_news.'\', \''.$ligne['id'].'\', NOW(), \''.$message.'\')';
			$bdd->exec($requete);
			header('Location: commentaire.php?num_news='.$num_news);
		}
		else
		{
			echo '<p>Pseudo ou mot de passe erron&eacute;<br /><a href="index.php">Retour &agrave; la page principale.</a></p>';
		}*/
		$resultat = $bdd->query('SELECT * FROM forum WHERE id="'.$num_news.'"');
		$ligne = $resultat->fetch();
		$resultat->closeCursor();
					
		if (strcmp($ligne['ferme'], '1') != 0)
		{
			$requete = 'INSERT INTO commentaire(num_news, pseudo, date, texte) VALUES (\''.$num_news.'\', \''.$_SESSION['idpseudo'].'\', NOW(), \''.$message.'\')';
			$bdd->exec($requete);
			$requete = 'UPDATE forum SET modification=NOW() WHERE id=\''.intval($num_news).'\'';
			$bdd->exec($requete);
			header('Location: forumTopic.php?num_news='.$num_news);
		}
		else
			header('Location: topic_ferme.php');
	}
	else
	{
		header('Location: commentaire_erreur.php');
	}
?>