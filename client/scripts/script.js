var request = new XMLHttpRequest();

request.onreadystatechange = function()
{
    if (request.readyState == XMLHttpRequest.DONE)
    {
        document.getElementById("msg").innerHTML = request.responseText;
    }
}
document.getElementById("form").submit = function()
{
    console.log("sdf");
    request.open("GET", "/?inputField=" + document.getElementById("form")[0].value + "&inputField2=" + document.getElementById("form")[1].value, true);
    request.send();
};







document.getElementById("button").addEventListener("click", function()
{
    document.getElementById("form")[0].value = "rock";
    document.getElementById("form")[1].value = "roll";
});