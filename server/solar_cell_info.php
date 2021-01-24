<?php
	/*
	** 
	** Alexander Chatterjee 23/01/2020
	**
	*/

	// Takes raw data from the request
	$json = file_get_contents('php://input');
	
	$localFileName = "solar_cell_info.txt";
	
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
				
			
			$dataFormat.="{";
			//print data of reception
			$dataFormat.="\"Date\":\"".date("Y-m-d H:i:s")."\",";
			
			//print temperature
			$dataFormat.="\"Temperature\":";
			if(isset($data->T))
				$dataFormat.= $data->T;
			else
				$dataFormat.="\"Error\"";
			$dataFormat.=",";	
			
			//print humidity
			$dataFormat.="\"Humidity\":";
			if(isset($data->H))
				$dataFormat.=$data->H;
			else
				$dataFormat.="\"Error\"";
			$dataFormat.=",";
			
			//print Solar cell voltage
			$dataFormat.="\"Cell-voltage\":";
			if(isset($data->VC))
				$dataFormat.=$data->VC;
			else
				$dataFormat.="\"Error\"";
			$dataFormat.=",";
			
			//print Open Circuit voltage
			$dataFormat.="\"Open-cuircuit\":";
			if(isset($data->OC))
				$dataFormat.=$data->OC;
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
