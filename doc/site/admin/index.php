<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta name="Robots" content="none">
		<meta name="GOOGLEBOT" content="noarchive">
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Fu(X) 2.0 - Administration</title>
	</head>
	<body>
		<?php
			require("../bdd.php");
		?>
		<h1>Administration du site</h1>
		<p><a href="../index.php">Accueil du site</a></p>
		<?php
			$afficheConnexion = true;
			if (isset($_POST['deco']))
			{
				unset($_SESSION['admin']);
				unset($_SESSION['idpseudo']);
				unset($_SESSION['pseudo']);
				unset($_SESSION['mdp']);
				unset($_SESSION['autorise']);
			}
			
			if (isset($_POST['admin_connex']) && isset($_POST['pseudo']) && isset($_POST['mdp']))
			{
				$pseudo = htmlentities($_POST['pseudo'], ENT_QUOTES);
				$mdp = htmlentities($_POST['mdp'], ENT_QUOTES);
				
				$requete = 'SELECT * FROM utilisateur WHERE pseudo="'.$pseudo.'"';
				$resultat = $bdd->query($requete);
				$ligne = $resultat->fetch();
				
				if ($ligne && strcmp($mdp, $ligne['mdp']) == 0)
				{
					if ($ligne['admin'] == 1)
					{
						$_SESSION['admin'] = true;
						$_SESSION['pseudo'] = $pseudo;
						$_SESSION['idpseudo'] = $ligne['id'];
						$_SESSION['mdp'] = $mdp;
						$_SESSION['autorise'] = ($ligne['autorise'] == 1);
						$afficheConnexion = false;
					}
					else
						echo '<p>Vous n\'avez pas les autorisations n&eacute;cessaires.</p>';
				}
				else
					echo '<p>Pseudo ou mot de passe faux.</p>';
				$resultat->closeCursor();
			}
			if (isset($_SESSION['admin']) && $_SESSION['admin'] == true)
			{
				echo '<p>Bienvenue '.$_SESSION['pseudo'].'</p>';
				$requeteAdminListe = 'SELECT pseudo FROM utilisateur WHERE admin="1"';
				$resultatAdminListe = $bdd->query($requeteAdminListe);
				
				$donnee = $resultatAdminListe->fetch();
				echo '<p>Administrateurs : '.$donnee['pseudo'];
				while($donnee = $resultatAdminListe->fetch())
					echo ', '.$donnee['pseudo'];
				echo '</p>';
				
				$requeteAdminListe = 'SELECT COUNT(*) FROM utilisateur';
				$resultatAdminListe = $bdd->query($requeteAdminListe);
				$donnee = $resultatAdminListe->fetch();
				echo '<p>'.$donnee[0].' inscrits</p>';
				
				$resultatAdminListe->closeCursor();
				
				?>
					<form action="index.php" method="post">
						<p>
							<input type="submit" value="D&eacute;connexion" />
							<input type="hidden" name="deco" value="on" />
						</p>
					</form>
					<h3>Mise &agrave; jour</h3>
					<p>
						<ul>
							<li><a href="ajoutNews.php">Actualit&eacute; : Ajouter une news / un nouveau sujet</a></li>
							<li><a href="ajoutVersion.php">Ajouter une version de Fu(X)</a></li>
							<li><a href="newsletter.php">Envoyer une newsletter - lettre d'information</a></li>
							<li><a href="reconstruireFluxRSS.php">Reconstruire le flux RSS</a></li>
						</ul>
					</p>
					<h3>Administration</h3>
					<p>
						<ul>
							<li><a href="ajoutRetraitAdmin.php">Ajouter/Retirer un admin</a></li>
						</ul><ul>
							<li><a href="deBloquer.php">Bloquer/Autoriser un utilisateur</a></li>
						</ul><ul>
							<li><a href="forumBloque.php">Fermer/Ouvrir un sujet</a></li>
						</ul>
					</p>
					
					<h3>SPAM</h3>
					<p><a href="newsletter_pourri.php">Pourrir une boite</a></p>
				<?php
			}
			else if ($afficheConnexion)
			{
			?>
				<form action="index.php" method="post">
					<fieldset>
						<legend>Connexion</legend>
						<table>
							<tr>
								<td><label for="idpseudo">Pseudo</label></td>
								<td><input type="text" name="pseudo" id="idpseudo" maxlength="25" value="<?php if (!empty($_SESSION['pseudo'])) echo $_SESSION['pseudo'];?>" /></td>
							</tr>
							<tr>
								<td><label for="idmdp">Mot de passe</label></td>
								<td><input type="password" name="mdp" id="idmdp" maxlength="25" value="<?php if (!empty($_SESSION['mdp'])) echo $_SESSION['mdp'];?>" /></td>
							</tr>
							<tr>
								<td></td>
								<td><input type="submit" value="S'authentifier" /><input type="hidden" name="admin_connex" value="on" /></td>
							</tr>
						</table>
					</fieldset>
				</form>
			<?php
			}
		?>
		
	</body>
</html>