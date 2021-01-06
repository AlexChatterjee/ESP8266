<?php
	/*
	** 
	** Alexander Chatterjee 31/12/2020
	**
	*/

	// Takes raw data from the request
	$json = file_get_contents('php://input');
	
	$localFileName = "temperatureAndHumidity.txt";
	
	if(isset($json))
	{
		echo "Transmition successful";
		// Converts it into a PHP object
		if($data = json_decode($json))
		{
			echo " Json Ok: ".$json;
			
			//check if file exist
			if(file_exists ($localFileName))
				$dataFormat=",";
			else
				$dataFormat="";
				
			
			$dataFormat.="{\"Date\":\"".date("Y-m-d H:i:s")."\",";
			$dataFormat.="\"Temperature\":";
			if(isset($data->T))
				$dataFormat.= $data->T;
			else
				$dataFormat.="\"Error\"";
			$dataFormat.=",";	
			
			$dataFormat.="\"Humidity\":";
			if(isset($data->H))
				$dataFormat.=$data->H;
			else
				$dataFormat.="\"Error\"";
			$dataFormat.="}";					
								
			//write in appending file
			$fp = fopen($localFileName, 'a');//opens file in append mode  
				fwrite($fp,$dataFormat);  
			fclose($fp);		
		}
		else
			echo " Json error";
	}
	else
	{
		echo "Transmission error: no payload has been sent correctly";
	}
	

?>
