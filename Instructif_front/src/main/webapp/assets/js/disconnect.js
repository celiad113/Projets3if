$(document).ready(function(){

    $("#bouton-deconnecter").click( function(){
    disconnect();
    });
})

function disconnect(){
    return $.ajax({
        type: "POST",
        url: "action-servlet?todo=deconnexion",

        success: function(){
            window.location.href = "login.html";
        },
        error: function(){
            console.log("Impossible de se deconecter");
        }
    })
}