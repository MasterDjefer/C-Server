var requestPostData = new XMLHttpRequest();
requestPostData.onreadystatechange = function()
{
    if (requestPostData.readyState == XMLHttpRequest.DONE)
    {
        console.log("Posted: " + requestPostData.responseText);
    }
}
document.getElementById("postData").onclick = function()
{
    if (document.getElementById("postForm")[0].value.trim() == "" || document.getElementById("postForm")[1].value.trim() == "")
    {
        alert("Fill all fields!");
        return;
    }

    requestPostData.open("POST", "/postData", true);
    let obj = document.getElementById("postForm")[0].name + "=" + document.getElementById("postForm")[0].value + "&" + 
              document.getElementById("postForm")[1].name + "=" + document.getElementById("postForm")[1].value;

    requestPostData.send(obj);
};

var requestGetData = new XMLHttpRequest();
requestGetData.onreadystatechange = function()
{
    if (requestGetData.readyState == XMLHttpRequest.DONE)
    {
        if (requestGetData.responseText == "Invalid index")
            alert("Input correct index!");
        else
            document.getElementById("dataLabel").innerHTML =  requestGetData.responseText;
    }
}
document.getElementById("getData").onclick = function()
{
    if (!Number(document.getElementById("getForm")[0].value))
    {
        alert("Input correct index!");
        return;
    }

    requestGetData.open("GET", "/getData?" + document.getElementById("getForm")[0].name + "=" + document.getElementById("getForm")[0].value, true);
    requestGetData.send();
};

var requestAllGetData = new XMLHttpRequest();
requestAllGetData.onreadystatechange = function()
{
    if (requestAllGetData.readyState == XMLHttpRequest.DONE)
    {
        document.getElementById("allDataLabel").innerHTML =  requestAllGetData.responseText;
        console.log(requestAllGetData.responseText);
    }
}
document.getElementById("getAllData").onclick = function()
{
    requestAllGetData.open("GET", "/getAllData", true);
    requestAllGetData.send();
};
