<?php
	/*
	** 
	** Alexander Chatterjee 2020
	**
	*/

	
	/*
	** build template to be sent
	*/

	if(isset($_REQUEST['ip'], $_REQUEST['data']))
	{
		$ip = $_REQUEST['ip'];
		$data = $_REQUEST['data'];
		
		echo "Data and IP received: IP:".$ip." \n data:".$data;
	}
	else
	{
		echo "Transmission error: no payload has been sent correctly";
	}

?>
