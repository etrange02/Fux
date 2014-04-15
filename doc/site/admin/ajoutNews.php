<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Fu(X) 2.0 - Administration News</title>
		<?php
			require("fonction.php");
			require("../bdd.php");
		?>
	</head>
	<body>
		<h1>Administration du site</h1>
		<p><a href="../index.php">Accueil du site</a></p>
		<p><a href="index.php">Accueil administration</a></p>
		<?php
			if (isset($_SESSION['admin']) && $_SESSION['admin'] == true)
			{
				echo '<p>Bienvenue '.$_SESSION['pseudo'].'</p>';
				?>
					<form action="index.php" method="post">
						<p>
							<input type="submit" value="D&eacute;connexion" />
							<input type="hidden" name="deco" value="on" />
						</p>
					</form>
					<form action="<?php $PHP_SELF;?>" method="post">
						<fieldset>
							<legend>Ajouter une news (Attention au code html entr&eacute;, il est pris en compte)</legend>
							<table>
							<tr>
								<td><label for="idtitre">Titre</label></td>
								<td><input type="text" id="idtitre" name="titre" size="100" maxlength="255" /></td>
							</tr>
							<tr>
								<td><label for="idtexte">News</label></td>
								<td><textarea id="idtexte" name="texte" cols="100" rows="6"></textarea></td>
							</tr>
							<tr>
								<td></td>
								<td><input type="submit" value="Poster" name="ajoutNews" /></td>
							</tr>
						</fieldset>
					</form>
				<?php
				if (isset($_POST['ajoutNews']))
				{
					$titre = utf8tohtml($_POST['titre'], true);
					//$texte = nl2br(htmlentities($_POST['texte'], ENT_QUOTES, 'UTF-8', false));
					$texte = utf8tohtml(nl2br($_POST['texte']), false);
					
					$requete = 'INSERT INTO forum(auteur, titre, ferme, modification) VALUES ('.$_SESSION['idpseudo'].', \''.$titre.'\', 0, NOW())';
					if ($bdd->exec($requete))
					{
						$identifiant = $bdd->lastInsertId('id');
						
						$requete = 'INSERT INTO commentaire(num_news, pseudo, date, texte) VALUES (\''.$identifiant.'\', \''.$_SESSION['idpseudo'].'\', NOW(), \''.$texte.'\')';
						$bdd->exec($requete);
						
						$requete = 'INSERT INTO news(auteur, titre, date, texte, forum) VALUES ('.$_SESSION['idpseudo'].', \''.$titre.'\', NOW(), \''.$texte.'\', \''.$identifiant.'\')';
						if($bdd->exec($requete))
							echo '<p>La news a &eacute;t&eacute; post&eacute;e';
						else
							echo '<p>La news n\'a pas pu &ecirc;tre ajout&eacute;e.</p>'.$requete;
					}
				}
			}
			else
				header('Location: index.php');
		?>
		
	</body>
</html>