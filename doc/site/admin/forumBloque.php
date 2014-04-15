<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Fu(X) 2.0 - Administration - Admin</title>
		<?php 
			require("../bdd.php");
			require("fonction.php");
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
							<legend>Statut topic</legend>
							<table>
							<tr>
								<td><label for="ididentifiant">identifiant</label></td>
								<td><input type="text" id="ididentifiant" name="identifiant" maxlength="255" title="Ce champ n'est pas prioritaire" /></td>
							</tr>
							<tr>
								<td><label for="idSujet">Sujet</label></td>
								<td><input type="text" id="idSujet" name="sujet" maxlength="255" title="Ce champ est prioritaire" /></td>
							</tr>
							<tr>
								<td></td>
								<td><label for="idOuvrir">Ouvrir</label>
								<input type="radio" id="idOuvrir" name="ouvreFerme" value="ouvrir" checked="checked" />
								<label for="idFermer">Fermer</label>
								<input type="radio" id="idFermer" name="ouvreFerme" value="fermer" /></td>
							</tr>
							<tr>
								<td></td>
								<td><input type="submit" value="Envoyer" name="modif" /></td>
							</tr>
						</fieldset>
					</form>
				<?php
				if (isset($_POST['modif']))
				{
					$id_forum = -1;
					if (isset($_POST['sujet']))
					{
						$sujet = utf8tohtml($_POST['sujet'], true);
						$requete = 'SELECT id, titre FROM forum WHERE titre=\''.$sujet.'\'';
						$resultat = $bdd->query($requete);
						$ligne = $resultat->fetch();
						if ($ligne)
							$id_forum = $ligne['id'];
						else if (isset($_POST['identifiant']))
							$id_forum = $_POST['identifiant'];
						else
							$id_forum = false;
						$resultat->closeCursor();
					}
					else if (isset($_POST['identifiant']))
					{
						$requete = 'SELECT id, titre FROM forum WHERE id=\''.$_POST['identifiant'].'\'';
						$resultat = $bdd->query($requete);
						$ligne = $resultat->fetch();
						$id_forum = $ligne['id'];
						$resultat->closeCursor();
					}
					else
						$id_forum = false;
					
					$deBloque = (strcmp($_POST['ouvreFerme'], 'fermer') == 0) ? 1 : 0;
					
					if ($id_forum)
					{
						$requete = 'UPDATE forum SET modification=NOW(), ferme=\''.$deBloque.'\' WHERE id=\''.intval($id_forum).'\'';
							
						if ($bdd->exec($requete))
							echo '<p>Modification r&eacute;ussite, id n&deg'.$id_forum.' - '.$ligne['titre'].' : '.( $deBloque ? 'ferm&eacute;' : 'ouvert').'</p>';
						else
							echo '<p>Echec de la modification</p>';
					}
				}
			}
			else
				header('Location: index.php');
		?>
		
	</body>
</html>