<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Fu(X) 2.0 - Administration - Admin</title>
		<?php require("../bdd.php"); ?>
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
							<legend>Statut utilisateur</legend>
							<table>
							<tr>
								<td><label for="ididentifiant">identifiant</label></td>
								<td><input type="text" id="ididentifiant" name="identifiant" maxlength="255" title="Ce champ n'est pas prioritaire" /></td>
							</tr>
							<tr>
								<td><label for="idpseudo">pseudo</label></td>
								<td><input type="text" id="idpseudo" name="pseudo" maxlength="255" title="Ce champ est prioritaire" /></td>
							</tr>
							<tr>
								<td></td>
								<td><label for="idAutoriser">Autoriser</label>
								<input type="radio" id="idAutoriser" name="deBloque" value="autoriser" checked="checked" />
								<label for="idBloquer">Bloquer</label>
								<input type="radio" id="idBloquer" name="deBloque" value="bloquer" /></td>
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
					$id_utilisateur = -1;
					if (isset($_POST['pseudo']))
					{
						$requete = 'SELECT id, admin, pseudo FROM utilisateur WHERE pseudo=\''.$_POST['pseudo'].'\'';
						$resultat = $bdd->query($requete);
						$ligne = $resultat->fetch();
						if ($ligne)
							$id_utilisateur = $ligne['id'];
						else if (isset($_POST['identifiant']))
							$id_utilisateur = $_POST['identifiant'];
						else
							$id_utilisateur = false;
						$resultat->closeCursor();
					}
					else if (isset($_POST['identifiant']))
					{
						$requete = 'SELECT id, admin, pseudo FROM utilisateur WHERE id=\''.$_POST['identifiant'].'\'';
						$resultat = $bdd->query($requete);
						$ligne = $resultat->fetch();
						$id_utilisateur = $ligne['id'];
						$resultat->closeCursor();
					}
					else
						$id_utilisateur = false;
					
					$deBloque = (strcmp($_POST['deBloque'], 'autoriser') == 0) ? 1 : 0;
					//Sécurité
					if (strcmp('etrange02', $_POST['pseudo']) == 0 || intval($id_utilisateur) == 1)
					{
						$id_utilisateur = false;
						echo '<p>Impossible de d&eacute;poss&eacute;der ce compte du droit d\'administrateur.</p>';
					}
					if (intval($ligne['admin']) == 1 && !$deBloque)
					{
						$id_utilisateur = false;
						echo '<p>Impossible d\'emp&ecirc;cher un administrateur de poster.</p>';
					}
					//
					
					if ($id_utilisateur)
					{
						$requete = 'UPDATE utilisateur SET autorise=\''.$deBloque.'\' WHERE id=\''.intval($id_utilisateur).'\'';
							
						if ($bdd->exec($requete))
							echo '<p>Modification r&eacute;ussite, id n&deg'.$id_utilisateur.' - '.$ligne['pseudo'].' : '.( $deBloque ? 'autoris&eacute;': 'bloqu&eacute;').'</p>';
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