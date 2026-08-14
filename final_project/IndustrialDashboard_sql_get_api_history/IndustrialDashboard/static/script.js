function update()
{
    fetch("/data")
    .then(response => response.json())
    .then(data => {

        document.getElementById("status").innerHTML = data.status;
        document.getElementById("temp").innerHTML = data.temp;
        document.getElementById("hum").innerHTML = data.hum;
        document.getElementById("vib").innerHTML = data.vib;

        /* Status */

        if(data.status === "SAFE")
        {
            document.getElementById("status").style.color = "lime";
        }
        else
        {
            document.getElementById("status").style.color = "red";
        }

        /* MQ2 Analog Detection */

        if(data.gas === 0)
        {
            document.getElementById("gas").innerHTML = "GAS DETECTED";
            document.getElementById("gas").style.color = "red";
        }
        else
        {
            document.getElementById("gas").innerHTML = "CLEAR";
            document.getElementById("gas").style.color = "lime";
        }

    })
    .catch(error => {

        console.log("Dashboard Error :", error);

    });
}

setInterval(update, 1000);

update();
