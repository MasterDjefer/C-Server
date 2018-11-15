var request = new XMLHttpRequest();
request.onreadystatechange = function()
{
    if (request.readyState == XMLHttpRequest.DONE)
    {
        document.getElementById("msg").innerHTML = request.responseText;
    }
}
document.getElementById("submitButton").onclick = function()
{
    request.open("GET", "/?name=" + document.getElementById("form")[0].value + "&age=" + document.getElementById("form")[1].value, true);   
    request.send();
};

var postRequest = new XMLHttpRequest();
postRequest.onreadystatechange = function()
{
    if (postRequest.readyState == XMLHttpRequest.DONE)
    {
        // document.getElementById("msg").innerHTML = postRequest.responseText;
        console.log(postRequest.responseText);
    }
}
document.getElementById("postButton").onclick = function()
{
    postRequest.open("POST", "/me", true);
    var obj = "name=pasha&age=16";
    postRequest.send(obj);
};







document.getElementById("button").addEventListener("click", function()
{
    document.getElementById("form")[0].value = "rock";
    document.getElementById("form")[1].value = "roll";
});