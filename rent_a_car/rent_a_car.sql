-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Aug 27, 2020 at 08:51 AM
-- Server version: 10.4.14-MariaDB
-- PHP Version: 7.2.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `rent a car`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `admin_id` int(255) UNSIGNED NOT NULL,
  `user_id` int(11) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`admin_id`, `user_id`) VALUES
(6, 41),
(55, 42);

-- --------------------------------------------------------

--
-- Table structure for table `bookings`
--

CREATE TABLE `bookings` (
  `id_reserv` int(10) UNSIGNED NOT NULL,
  `user_id` int(11) UNSIGNED NOT NULL,
  `car_id` int(11) UNSIGNED NOT NULL,
  `user_name` varchar(11) NOT NULL,
  `date_from` date NOT NULL,
  `date_to` date NOT NULL,
  `pick_up` text NOT NULL,
  `return_loca` text NOT NULL,
  `message` mediumtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Triggers `bookings`
--
DELIMITER $$
CREATE TRIGGER `history_reserv` BEFORE DELETE ON `bookings` FOR EACH ROW BEGIN
INSERT INTO canceled_resrv (reserv_id,user_id,username,datefrom,dateto,from_loc,to_loc,action)
VALUES(old.id_reserv,user_id,old.user_name,
   old.date_from,old.date_to,old.pick_up,old.return_loca,'cancelled');
END
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `canceled_resrv`
--

CREATE TABLE `canceled_resrv` (
  `id` int(11) NOT NULL,
  `reserv_id` int(255) NOT NULL,
  `user_id` int(255) UNSIGNED NOT NULL,
  `username` varchar(22) NOT NULL,
  `datefrom` date NOT NULL,
  `dateto` date NOT NULL,
  `from_loc` varchar(22) NOT NULL,
  `to_loc` varchar(22) NOT NULL,
  `action` varchar(22) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `canceled_resrv`
--

INSERT INTO `canceled_resrv` (`id`, `reserv_id`, `user_id`, `username`, `datefrom`, `dateto`, `from_loc`, `to_loc`, `action`) VALUES
(52, 77, 0, 'Виктор', '2020-08-25', '2020-08-27', 'Skopje', 'Belgrad', 'cancelled'),
(53, 75, 0, 'nekoj', '2020-08-25', '2020-08-28', 'Skopje', 'Belgrad', 'cancelled');

-- --------------------------------------------------------

--
-- Table structure for table `cars`
--

CREATE TABLE `cars` (
  `car_id` int(255) UNSIGNED NOT NULL,
  `brand` varchar(255) NOT NULL,
  `model` varchar(255) NOT NULL,
  `persons` int(255) NOT NULL,
  `transmission` varchar(255) NOT NULL,
  `price` int(255) NOT NULL,
  `luggage` int(255) NOT NULL,
  `air_conditioning` varchar(30) NOT NULL,
  `image` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `cars`
--

INSERT INTO `cars` (`car_id`, `brand`, `model`, `persons`, `transmission`, `price`, `luggage`, `air_conditioning`, `image`) VALUES
(3, 'Ford', 'Focus', 5, 'Manual', 35, 2, 'Air Conditioning', 'ford-focus.jpg'),
(29, 'Volkswagen', 'Passat', 5, 'Automatic', 50, 2, 'Air Conditioning', 'vw-passat.jpg'),
(31, 'Volkswagen', 'Golf', 5, 'Manual', 40, 1, 'Air Conditioning', 'vw-golf.jpg'),
(32, 'Audi', 'A5', 5, 'Manual', 40, 3, 'Air', 'audi.jpg');

-- --------------------------------------------------------

--
-- Table structure for table `contactus`
--

CREATE TABLE `contactus` (
  `id` int(10) UNSIGNED NOT NULL,
  `firstname` varchar(11) NOT NULL,
  `lastname` varchar(11) NOT NULL,
  `ph_number` int(11) NOT NULL,
  `email` varchar(255) NOT NULL,
  `message` varchar(255) NOT NULL,
  `user_id` int(10) UNSIGNED DEFAULT NULL,
  `date_submit` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `contactus`
--

INSERT INTO `contactus` (`id`, `firstname`, `lastname`, `ph_number`, `email`, `message`, `user_id`, `date_submit`) VALUES
(5338, 'некој11', 'некој', 98724623, 'viktordimitrioski@hotmail.com', 'асдасд', NULL, '2020-06-12'),
(5340, 'некој', 'некој', 98724623, 'viktor1@hotmail.com', 'асдасд', NULL, '2020-06-12'),
(5342, 'adad', 'wfdf', 98724623, 'viktor1@hotmail.com', 'hasdh123lasd123', NULL, '2020-08-23'),
(5343, 'adad', 'wfdf', 98724623, 'viktor1@hotmail.com', 'hasdh123lasd123', NULL, '2020-08-23'),
(5344, 'adad', 'wfdf', 98724623, 'viktor1@hotmail.com', 'hasdh123lasd123', NULL, '2020-08-23'),
(5346, 'adad', 'wfdf', 98724623, 'viktor1@hotmail.com', 'hasdh123lasd123', NULL, '2020-08-23'),
(5347, 'adad', 'wfdf', 98724623, 'viktor1@hotmail.com', 'hasdh123lasd123', NULL, '2020-08-23'),
(5348, 'Виктор', 'Димитриоски', 2147483647, 'viktoasljdvaskgvds@hotmail.com', '33112255', NULL, '2020-08-23'),
(5349, 'Viktor', 'Dimitrioski', 123, 'viktor.102197@student.ugd.edu.mk', '123123', NULL, '2020-08-26');

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `id` int(255) UNSIGNED NOT NULL,
  `username` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL,
  `firstname` varchar(255) NOT NULL,
  `lastname` varchar(255) NOT NULL,
  `city` varchar(11) DEFAULT NULL,
  `country` varchar(11) DEFAULT NULL,
  `address` varchar(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`id`, `username`, `password`, `email`, `firstname`, `lastname`, `city`, `country`, `address`) VALUES
(41, 'Борјан', 'da112714fd443529b4202364c3102857', 'borjan@hotmail.com', 'Борјан', 'Димитриоски', '', 'Македонија', ''),
(42, 'Виктор', 'a3bf77154e034179c24176bff88e8f31', 'dfdf@hotmail.com', 'Виктор', 'Димитриоски', '', '', ''),
(44, 'askdjaskjd', 'a3bf77154e034179c24176bff88e8f31', 'ajhsdbajhsdajs@123123123', 'viktor1', 'Dimitrioski', '', '', ''),
(45, 'nekoj', 'a3bf77154e034179c24176bff88e8f31', 'nekoj@hotmail.com', 'nekoj', 'nekoj', 'nekoj', 'nekoj', 'nekoj');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`admin_id`),
  ADD KEY `user_id` (`user_id`);

--
-- Indexes for table `bookings`
--
ALTER TABLE `bookings`
  ADD PRIMARY KEY (`id_reserv`),
  ADD KEY `car_id` (`car_id`),
  ADD KEY `user_id` (`user_id`);

--
-- Indexes for table `canceled_resrv`
--
ALTER TABLE `canceled_resrv`
  ADD PRIMARY KEY (`id`),
  ADD KEY `user_id` (`user_id`);

--
-- Indexes for table `cars`
--
ALTER TABLE `cars`
  ADD PRIMARY KEY (`car_id`);

--
-- Indexes for table `contactus`
--
ALTER TABLE `contactus`
  ADD PRIMARY KEY (`id`),
  ADD KEY `user_id` (`user_id`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `username` (`username`),
  ADD UNIQUE KEY `email` (`email`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `admin`
--
ALTER TABLE `admin`
  MODIFY `admin_id` int(255) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=56;

--
-- AUTO_INCREMENT for table `bookings`
--
ALTER TABLE `bookings`
  MODIFY `id_reserv` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=78;

--
-- AUTO_INCREMENT for table `canceled_resrv`
--
ALTER TABLE `canceled_resrv`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=54;

--
-- AUTO_INCREMENT for table `cars`
--
ALTER TABLE `cars`
  MODIFY `car_id` int(255) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=34;

--
-- AUTO_INCREMENT for table `contactus`
--
ALTER TABLE `contactus`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5350;

--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `id` int(255) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=46;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `admin`
--
ALTER TABLE `admin`
  ADD CONSTRAINT `admin_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `user` (`id`);

--
-- Constraints for table `bookings`
--
ALTER TABLE `bookings`
  ADD CONSTRAINT `bookings_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `user` (`id`),
  ADD CONSTRAINT `bookings_ibfk_2` FOREIGN KEY (`car_id`) REFERENCES `cars` (`car_id`);

--
-- Constraints for table `contactus`
--
ALTER TABLE `contactus`
  ADD CONSTRAINT `contactus_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `user` (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
