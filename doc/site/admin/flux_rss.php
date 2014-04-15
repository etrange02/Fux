<?php
	include("../bdd.php");
	
	function &init_news_rss(&$xml_file)
	{
		$root = $xml_file->createElement("rss");
		$root->setAttribute("version", "2.0");
		$root = $xml_file->appendChild($root);
		
		$channel = $xml_file->createElement("channel");
		$channel = $root->appendChild($channel);
		
		$desc = $xml_file->createElement("description");
		$desc = $channel->appendChild($desc);
		$text_desc = $xml_file->createTextNode('Téléchargez la dernière version de Fu(X) correspondant à votre ordinateur');
		$text_desc = $desc->appendChild($text_desc);
		
		$link = $xml_file->createElement("link");
        $link = $channel->appendChild($link);
        $text_link = $xml_file->createTextNode("http://www.fuxplay.com");
        $text_link = $link->appendChild($text_link);
        
        $title = $xml_file->createElement("title");
        $title = $channel->appendChild($title);
        $text_title = $xml_file->createTextNode("Fu(X) 2.0 - www.fuxplay.com");
        $text_title = $title->appendChild($text_title);
		
		return $channel;
	}
	
	//function add_news_node(&$parent, $root, $id, $pseudo, $titre, $contenu, $date)
	function add_news_node(&$parent, $root, $titre, $lien, $contenu, $date)
	{
        $item = $parent->createElement("item");
        $item = $root->appendChild($item);
        
        $title = $parent->createElement("title");
        $title = $item->appendChild($title);
        $text_title = $parent->createTextNode($titre);
        $text_title = $title->appendChild($text_title);
        
        $link = $parent->createElement("link");
        $link = $item->appendChild($link);
        $text_link = $parent->createTextNode("http://www.fuxplay.com/".$lien);
        $text_link = $link->appendChild($text_link);
        
        $desc = $parent->createElement("description");
        $desc = $item->appendChild($desc);
        $text_desc = $parent->createTextNode('T&eacute;l&eacute;chargez la derni&egrave;re version de Fu(X) - '.$contenu);
        $text_desc = $desc->appendChild($text_desc);
        
        /*$com = $parent->createElement("comments");
        $com = $item->appendChild($com);
        $text_com = $parent->createTextNode("http://www.bougiemind.info/news-11-".$id.".html");
        $text_com = $com->appendChild($text_com);*/
        
        /*$author = $parent->createElement("author");
        $author = $item->appendChild($author);
        $text_author = $parent->createTextNode($pseudo);
        $text_author = $author->appendChild($text_author);*/
        
        $pubdate = $parent->createElement("pubDate");
        $pubdate = $item->appendChild($pubdate);
        $text_date = $parent->createTextNode($date);
        $text_date = $pubdate->appendChild($text_date);
        
        /*$guid = $parent->createElement("guid");
        $guid = $item->appendChild($guid);
        $text_guid = $parent->createTextNode("http://www.bougiemind.info/rss_news".$id.".html");
        $text_guid = $guid->appendChild($text_guid);*/
        
        $src = $parent->createElement("source");
        $src = $item->appendChild($src);
        $text_src = $parent->createTextNode("http://www.fuxplay.com");
        $text_src = $src->appendChild($text_src);
	}
	
	function rebuild_rss($bdd)
	{
        // on se connecte à la BDD		
		
		if ($bdd)
			echo 'MAJ flux RSS : oui';
		else
			echo 'MAJ flux RSS : non';
		$requete = 'SELECT * FROM version ORDER BY id DESC LIMIT 0, 1';
		$resultat = $bdd->query($requete);
		$ligne = $resultat->fetch();
		$ver = $ligne['version'];
		$resultat->closeCursor();
			
		$requete = 'SELECT * FROM version ORDER BY version DESC LIMIT 0, 4';// WHERE version=\''.$ver.'\'';
		$res = $bdd->query($requete);
        
        // on crée le fichier XML
        $xml_file = new DOMDocument("1.0");//, "UTF-8");
		
		$channel = init_news_rss($xml_file);
 
        // on ajoute chaque news au fichier RSS
        while($news = $res->fetch())
        {
			add_news_node($xml_file, $channel, utf8_encode($news['nom']), $news['lien'], htmlentities($news['nom']), date("d/m/Y H:i", $news['parution']));	
            //add_news_node($xml_file, $channel, $news["nws_id"], $news["nws_pseudo"], $news["nws_titre"], $news["nws_contenu"], date("d/m/Y H:i", $news["nws_date"]));
        }
        $res->closeCursor();
        // on écrit le fichier
        $xml_file->save("../download_fux_rss.xml");
	}
?>