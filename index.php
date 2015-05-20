<?php
/*
* PHP Script part of https://github.com/jurjendevries/doorbell-to-web/
* This script sends a notification by Pushbullet when it's triggered by the Particle core door bell pin.
*
* You have to add Pushbullet.php v2.10.1 from https://github.com/ivkos/Pushbullet-for-PHP/tree/2.10.1/src in the same directory
*
* Script configuration:
* - Get an API key from pushbullet and add it to the $apikey line
* - Change the 'your-email-address-here@domain.tld' into your e-mail address
*/

require "Pushbullet.php";

// API key op PushBullet account: https://www.pushbullet.com/account
$apikey = "your-key-here";

try {
    $p = new PushBullet($apikey);
    $p->pushNote('your-email-address-here@domain.tld', 'Tring', 'This is the doorbell. Wooohooo!');
} catch (PushBulletException $e) {
    // Error handeling
    die($e->getMessage());
}
?>
