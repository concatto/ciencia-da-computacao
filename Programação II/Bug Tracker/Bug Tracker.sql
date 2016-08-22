
CREATE DATABASE IF NOT EXISTS bug_tracker;

use bug_tracker;


CREATE TABLE IF NOT EXISTS `bugs` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `titulo` varchar(50) NOT NULL,
  `status` tinyint(1) NOT NULL,
  `descricao` varchar(500) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

INSERT INTO `bugs` (`id`, `titulo`, `status`, `descricao`) VALUES
(1, 'Bug para teste', 1, 'testando a descrição'),
(2, 'mais um bug', 0, 'testando');

