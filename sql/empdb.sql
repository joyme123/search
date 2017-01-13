-- MySQL dump 10.13  Distrib 5.7.16, for Linux (x86_64)
--
-- Host: 115.29.114.202    Database: empdb
-- ------------------------------------------------------
-- Server version	5.7.16-0ubuntu0.16.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `document`
--

DROP TABLE IF EXISTS `document`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `document` (
  `id` int(20) NOT NULL AUTO_INCREMENT,
  `srcFlg` int(11) DEFAULT NULL,
  `title` varchar(255) NOT NULL,
  `type` int(2) NOT NULL,
  `abstract` varchar(255) NOT NULL,
  `url` varchar(255) NOT NULL,
  `author` varchar(255) NOT NULL,
  `text` text NOT NULL,
  `wordNum` int(30) DEFAULT NULL,
  `updateTime` datetime NOT NULL,
  `createTime` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=10119 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `document`
--

LOCK TABLES `document` WRITE;
/*!40000 ALTER TABLE `document` DISABLE KEYS */;
INSERT INTO `document` VALUES (10116,NULL,'Java虚拟机学习记录(九)——类文件结构(上)',1,'Friso是使用c语言开发的一款开源的高性能中文分词器，使用流','http://myway5.com/?post=54','joyme','Friso是使用c语言开发的一款开源的高性能中文分词器，使用流行的mmseg算法实现。完全基于模块化设计和实现，可以很方便的植入其他程序中，例如：MySQL，PHP，源码无需修改就能在各种平台下编译使用，加载完20万的词条，内存占用稳定为14.5M.',0,'2016-11-30 20:47:44','2016-11-30 20:47:44'),(10117,NULL,'Java虚拟机学习记录(九)——类文件结构(上)',1,'Friso是使用c语言开发的一款开源的高性能中文分词器，使用流','http://myway5.com/?post=54','joyme','Friso是使用c语言开发的一款开源的高性能中文分词器，使用流行的mmseg算法实现。完全基于模块化设计和实现，可以很方便的植入其他程序中，例如：MySQL，PHP，源码无需修改就能在各种平台下编译使用，加载完20万的词条，内存占用稳定为14.5M.',0,'2016-11-30 20:48:25','2016-11-30 20:48:25'),(10118,NULL,'Java虚拟机学习记录(九)——类文件结构(上)',1,'Friso是使用c语言开发的一款开源的高性能中文分词器，使用流','http://myway5.com/?post=54','joyme','Friso是使用c语言开发的一款开源的高性能中文分词器，使用流行的mmseg算法实现。完全基于模块化设计和实现，可以很方便的植入其他程序中，例如：MySQL，PHP，源码无需修改就能在各种平台下编译使用，加载完20万的词条，内存占用稳定为14.5M.',0,'2016-12-01 16:34:03','2016-12-01 16:34:03');
/*!40000 ALTER TABLE `document` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `simhash`
--

DROP TABLE IF EXISTS `simhash`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `simhash` (
  `id` int(30) NOT NULL AUTO_INCREMENT,
  `simhash` varchar(128) NOT NULL,
  `docIds` text NOT NULL,
  `createTime` datetime NOT NULL,
  `updateTime` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `simhash` (`simhash`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `simhash`
--

LOCK TABLES `simhash` WRITE;
/*!40000 ALTER TABLE `simhash` DISABLE KEYS */;
/*!40000 ALTER TABLE `simhash` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `word`
--

DROP TABLE IF EXISTS `word`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `word` (
  `id` int(20) NOT NULL AUTO_INCREMENT,
  `word` varchar(10) NOT NULL,
  `postingList` text NOT NULL,
  `docCount` int(30) NOT NULL,
  `totalCount` int(30) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=225 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `word`
--

LOCK TABLES `word` WRITE;
/*!40000 ALTER TABLE `word` DISABLE KEYS */;
INSERT INTO `word` VALUES (169,'.','(10116,1)<69>(10117,1)<69>(10118,1)<69>',3,3),(170,'14','(10116,1)<67>(10117,1)<67>(10118,1)<67>',3,3),(171,'14.5m','(10116,1)<68>(10117,1)<68>(10118,1)<68>',3,3),(172,'20','(10116,1)<58>(10117,1)<58>(10118,1)<58>',3,3),(173,'c语言','(10116,1)<4>(10117,1)<4>(10118,1)<4>',3,3),(174,'friso','(10116,1)<1>(10117,1)<1>(10118,1)<1>',3,3),(175,'mmseg','(10116,1)<18>(10117,1)<18>(10118,1)<18>',3,3),(176,'mysql','(10116,1)<40>(10117,1)<40>(10118,1)<40>',3,3),(177,'php','(10116,1)<42>(10117,1)<42>(10118,1)<42>',3,3),(178,'。','(10116,1)<21>(10117,1)<21>(10118,1)<21>',3,3),(179,'一款','(10116,1)<7>(10117,1)<7>(10118,1)<7>',3,3),(180,'万','(10116,1)<59>(10117,1)<59>(10118,1)<59>',3,3),(181,'下','(10116,1)<52>(10117,1)<52>(10118,1)<52>',3,3),(182,'中','(10116,1)<36>(10117,1)<36>(10118,1)<36>',3,3),(183,'中文','(10116,1)<11>(10117,1)<11>(10118,1)<11>',3,3),(184,'为','(10116,1)<66>(10117,1)<66>(10118,1)<66>',3,3),(185,'使用','(10116,3)<3,15,54>(10117,3)<3,15,54>(10118,3)<3,15,54>',3,9),(186,'例如','(10116,1)<38>(10117,1)<38>(10118,1)<38>',3,3),(187,'修改','(10116,1)<46>(10117,1)<46>(10118,1)<46>',3,3),(188,'其他','(10116,1)<34>(10117,1)<34>(10118,1)<34>',3,3),(189,'内存','(10116,1)<63>(10117,1)<63>(10118,1)<63>',3,3),(190,'分词器','(10116,1)<13>(10117,1)<13>(10118,1)<13>',3,3),(191,'加载','(10116,1)<56>(10117,1)<56>(10118,1)<56>',3,3),(192,'占用','(10116,1)<64>(10117,1)<64>(10118,1)<64>',3,3),(193,'可以','(10116,1)<29>(10117,1)<29>(10118,1)<29>',3,3),(194,'各种','(10116,1)<50>(10117,1)<50>(10118,1)<50>',3,3),(195,'和','(10116,1)<26>(10117,1)<26>(10118,1)<26>',3,3),(196,'国语','(10116,1)<12>(10117,1)<12>(10118,1)<12>',3,3),(197,'在','(10116,1)<49>(10117,1)<49>(10118,1)<49>',3,3),(198,'基于','(10116,1)<23>(10117,1)<23>(10118,1)<23>',3,3),(199,'完','(10116,1)<57>(10117,1)<57>(10118,1)<57>',3,3),(200,'完全','(10116,1)<22>(10117,1)<22>(10118,1)<22>',3,3),(201,'实现','(10116,2)<20,27>(10117,2)<20,27>(10118,2)<20,27>',3,6),(202,'就','(10116,1)<47>(10117,1)<47>(10118,1)<47>',3,3),(203,'平台','(10116,1)<51>(10117,1)<51>(10118,1)<51>',3,3),(204,'开发','(10116,1)<5>(10117,1)<5>(10118,1)<5>',3,3),(205,'开源','(10116,1)<8>(10117,1)<8>(10118,1)<8>',3,3),(206,'很','(10116,1)<30>(10117,1)<30>(10118,1)<30>',3,3),(207,'方便','(10116,1)<31>(10117,1)<31>(10118,1)<31>',3,3),(208,'无需','(10116,1)<45>(10117,1)<45>(10118,1)<45>',3,3),(209,'是','(10116,1)<2>(10117,1)<2>(10118,1)<2>',3,3),(210,'植入','(10116,1)<33>(10117,1)<33>(10118,1)<33>',3,3),(211,'模块化','(10116,1)<24>(10117,1)<24>(10118,1)<24>',3,3),(212,'流行','(10116,1)<16>(10117,1)<16>(10118,1)<16>',3,3),(213,'源码','(10116,1)<44>(10117,1)<44>(10118,1)<44>',3,3),(214,'的','(10116,5)<6,9,17,32,60>(10117,5)<6,9,17,32,60>(10118,5)<6,9,17,32,60>',3,15),(215,'程序','(10116,1)<35>(10117,1)<35>(10118,1)<35>',3,3),(216,'稳定','(10116,1)<65>(10117,1)<65>(10118,1)<65>',3,3),(217,'算法','(10116,1)<19>(10117,1)<19>(10118,1)<19>',3,3),(218,'编译','(10116,1)<53>(10117,1)<53>(10118,1)<53>',3,3),(219,'能','(10116,1)<48>(10117,1)<48>(10118,1)<48>',3,3),(220,'设计','(10116,1)<25>(10117,1)<25>(10118,1)<25>',3,3),(221,'词条','(10116,1)<61>(10117,1)<61>(10118,1)<61>',3,3),(222,'高性能','(10116,1)<10>(10117,1)<10>(10118,1)<10>',3,3),(223,'，','(10116,7)<14,28,37,41,43,55,62>(10117,7)<14,28,37,41,43,55,62>(10118,7)<14,28,37,41,43,55,62>',3,21),(224,'：','(10116,1)<39>(10117,1)<39>(10118,1)<39>',3,3);
/*!40000 ALTER TABLE `word` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-01-13 16:12:12
