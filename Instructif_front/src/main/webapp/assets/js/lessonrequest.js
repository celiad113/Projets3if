$(document).ready(function() {

    initMatieres().then(infosCoursEnAttente);

/*    $("#bouton-demande").click(function (e) {
        e.preventDefault();
        let matiere = document.getElementById("optionsList").value;
        let message = document.getElementById("message").value;
        console.log(matiere, message)

        $.ajax({
            type: "POST",
            url: `action-servlet?todo=demande-de-cours`,
            data : {
                matiere : matiere,
                message : message,
            },
            success: function (response){
                $('#error-message').empty();
                console.log(response.cours)

                if (response.cours != null) {

                    cours = response.cours;

                    // On stock en local l'id du cours actuel
                    localStorage.setItem('cours_actuel_id', response.cours.id)

                    // On renseigne les infos de l'intervenant dans le champ concerné
                    let intervenantInfo = $("#infoIntervenant");
                    intervenantInfo.innerText = response.cours.intervenant.prenom + " " + response.cours.intervenant.nom

                    // On stock les infos de l'intervenant en local
                    localStorage.setItem("nomIntervenant", response.cours.intervenant.nom)
                    localStorage.setItem("prenomIntervenant", response.cours.intervenant.prenom)

                    // rendre le bouton et les zones de textes non cliquable pendant une consultation
                    $("#bouton-demande").prop("disabled",true);
                    $("#message").prop("disabled",true);

                    terminerVisio();
                }
                else {
                    document.getElementById("formulaire").innerHTML += "Aucun Enseignant n'est disponible pour le moment, merci de réessayer dans 15 minutes"
                }
            },
            error: function () {
                console.log("Echec de la demande")
            }
        })
    })*/
    $("#bouton-demande").click(function(e){
        e.preventDefault();

        var data = {
            matiere: document.getElementById("optionsList").value,
            message: document.getElementById("message").value
        }

        demandeCours(data);
    });


    $("#bouton-raccrocher").click(function(){
        terminerVisio();
    });

});

function initMatieres(){
    return $.ajax({
        type: 'GET',
        url: `action-servlet?todo=afficher-matieres`,
        dataType: "json",

        success: function(response) {
            $('#error-message').empty();

            response.matieres.forEach(function (matiere){
                var option = $('<option></option>').val(matiere.id).html(matiere.nom);
                $('#optionsList').append(option);
            })
        },
        error: function() {
            // Handle any errors that occur during the AJAX request
            console.log("Erreur dans l'affichage des matieres");
        }
    });
}
function terminerVisio(){

    return $.ajax({
        type: 'POST',
        url: `action-servlet?todo=terminerVisio`,
        success: function (response) {
            $('#error-message').empty();
            console.log(response);

            $("#note").removeClass("visually-hidden");
            $("#note").modal('show');

            const etoiles = $(".etoiles .col button");
            let isClicked = false;
            let clickedEtoile = -1;
            console.log(etoiles);
            // TODO: trouver un moyen de select tous les boutons jusqu'a celui qu'on hover
            etoiles.each(function(index, etoile){
                $(etoile).hover(
                    function(){

                        let startIndex;
                        if(clickedEtoile < 0 ){
                            startIndex = 0;
                        }
                        else {
                            startIndex = clickedEtoile;
                        }

                        for(let i = startIndex ; i <= index ; i++){
                            $(etoiles[i]).children().removeClass("far").addClass("fas");
                        }
                    },
                    function(){
                        for(let i = clickedEtoile + 1 ; i <= index ; i++){
                            $(etoiles[i]).children().removeClass("fas").addClass("far");
                        }
                    }
                )

                $(etoile).click(function () {
                    isClicked = true;
                    clickedEtoile = index;
                    for(let i = 0 ; i <= index ; i++){
                        $(etoiles[i]).children().removeClass("far").addClass("fas");
                    }
                    for(let i = clickedEtoile + 1 ; i < 5 ; i++){
                        $(etoiles[i]).children().removeClass("fas").addClass("far");
                    }
                    $("#envoyernote").prop("disabled", false);
                    note = $(this)[0].value;
                    console.log(note);
                })
            });

            $('#envoyernote').click(function (){
                $.ajax({
                    type:'POST',
                    url: `action-servlet?todo=noterCours`,
                    data: { note : note },
                    success: function (response) {
                        $("#note").modal('hide');
                        location.reload();
                    },
                    error: function (){
                        console.log("Erreur lors de la notation")
                    }
                })
            })
        },
        error: function () {
            // Handle any errors that occur during the AJAX request
            console.log("Erreur lors de la fin du cours");
        }
    })

}

function infosCoursEnAttente(){
    return $.ajax({
        method: "GET",
        url: "action-servlet?todo=espace-eleve",
        dataType: "json",

        success: function(response){
            console.log(response);
            const cours = response.eleve.cours;

            console.log(cours);

            if(!isJsonObjectEmpty(cours)){
                $("#optionsList").val(cours.matiere.id);
                lockDemande(cours.message);
                displayVisio(cours.intervenant.prenom, cours.intervenant.nom);
            }
        },
        error: function(){
            console.log("ono :(");
        }
    })
}

function demandeCours(data){
    return $.ajax({
            method: "POST",
            url: "action-servlet?todo=demande-de-cours",
            data: {
                matiere: data.matiere,
                message: data.message
            },
            success: function(response){
                console.log(response.cours);

                if(!isJsonObjectEmpty(response)){
                    displayVisio(response.cours.intervenant.prenom, response.cours.intervenant.nom);
                    lockDemande(data.message);
                }
                else{
                    $("#alerteIndisponibilite").removeClass("visually-hidden");
                    console.log("Le cours n'a pas pu être créé");
                }
            },
            error: function(){
                console.error("yelp..");
            }
    });
}

function lockDemande(message){
    $("#bouton-demande").prop("disabled", true);
    $("#message").html(message);
    $("#message").prop("disabled", true);
    $('#optionsList').prop('disabled', true);
}
function displayVisio(prenom, nom){
    $("#noVisio").addClass("visually-hidden");
    $("#infoIntervenant").html(`${prenom} ${nom}`);
    $("#visio").removeClass("visually-hidden");
}

function isJsonObjectEmpty(jsonObject) {
    for (var key in jsonObject) {
        if (jsonObject.hasOwnProperty(key)) {
            return false; // The object has at least one property, so it is not empty
        }
    }
    return true; // The object has no properties, indicating it is empty
}