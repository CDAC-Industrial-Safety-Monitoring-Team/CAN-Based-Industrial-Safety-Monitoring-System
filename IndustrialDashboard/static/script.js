function update()
{

fetch("/data")

.then(response=>response.json())

.then(data=>{

document.getElementById("status").innerHTML=data.status;
document.getElementById("temp").innerHTML=data.temp;
document.getElementById("hum").innerHTML=data.hum;
document.getElementById("vib").innerHTML=data.vib;

if(data.status=="SAFE")
{
document.getElementById("status").style.color="lime";
}
else
{
document.getElementById("status").style.color="red";
}

});

}

setInterval(update,1000);

update();
