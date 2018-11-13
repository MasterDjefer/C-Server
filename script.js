var request = new XMLHttpRequest();

document.getElementById("button").addEventListener("click", function()
{
    request.open("GET", "/?inputField=45&inputField2=78", true);
    request.send();
});

request.onreadystatechange = function()
{
    if (request.readyState == XMLHttpRequest.DONE)
    {
        console.log(request.responseText);
        // document.getElementById("inputField").value = request.responseText;
    }
}