<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Fu(X) 2.0 - Administration Version</title>
		<?php
			include("../bdd.php"); 
			include("flux_rss.php");
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
					<form enctype="multipart/form-data" action="<?php $PHP_SELF;?>" method="post">
						<fieldset>
							<legend>Ajouter une version de Fu(X)</legend>
							<table>
							<tr>
								<td><label for="idversion">Version</label></td>
								<td><input type="text" id="idversion" name="version" size="3" maxlength="3" title="Ce doit &ecirc;tre le codage du type a12" <?php if (isset($_POST['ajoutVers'])) echo 'value="'.$_POST['version'].'"'; ?> /></td>
							</tr>
							<tr>
								<td><label for="idsource">Fichier &agrave; envoyer</label></td>
								<td><input type="file" id="idsource" name="source" size="100" /></td>
							</tr>
							<tr>
								<td><label for="idnom">Nom &agrave; afficher</label></td>
								<td><input type="text" id="idnom" name="nom" size="100" maxlength="255" /></td>
							</tr>
							<tr>
								<td></td>
								<td><input type="submit" value="Envoyer" name="ajoutVers" /></td>
							</tr>
						</fieldset>
					</form>
				<?php
				rebuild_rss($bdd);
				if (isset($_POST['ajoutVers']))
				{
					$lien_source = '';
					$erreur1 = false;
					if ($_FILES['source']['error'])
						echo '<p>erreur : '.$_FILES['source']['error'].'</p>';
					
					if (isset($_FILES['source']['name']))
					{
						/* Info : Le dossier de destination existe déjà et possède tous les droits nécessaire */
						if (move_uploaded_file($_FILES['source']['tmp_name'], '../telechargement/'.$_FILES['source']['name']))
							$lien_source = './telechargement/'.$_FILES['source']['name'];
						else
							$erreur1 = true;
					}
					
					$requete = 'INSERT INTO version(version, lien, nom) VALUES (\''.$_POST['version'].'\', \''.$lien_source.'\', \''.$_POST['nom'].'\')';
					if (!$erreur1)
					{
						if($bdd->exec($requete))
							echo '<p>Envoi r&eacute;ussi de <span id="rouge">'.$_FILES['source']['name'].'</span> ('.$_FILES['source']['tmp_name'].')</p>';
						else
							echo '<p>La base de donn&eacute;es n\'a pas pu &ecirc;tre mise &agrave; jour.</p>';
						rebuild_rss($bdd);
					}
					else
						echo '<p>Le fichier n\'a pas pu &ecirc;tre transmis.</p>';
				}
			}
			else
				header('Location: index.php');
		?>
		
	</body>
</html>