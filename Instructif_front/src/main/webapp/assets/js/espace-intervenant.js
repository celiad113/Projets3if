$(document).ready(function() {

    $.ajax({
        type: "GET",
        url: "action-servlet?todo=espace-intervenant",
        dataType: "json",

        success: function(response){

            // Extract properties into variables
            if(!isJsonObjectEmpty(response)){
                var id = response.id;

                var eleve = response.eleve;
                var prenom = capitalizeFirstLetter(eleve.prenom);
                var nom = capitalizeFirstLetter(eleve.nom);
                var niveau = eleve.niveau;
                var etablissement = eleve.etablissement;

                var matiere = response.matiere;
                var commentaire = response.commentaire;

                $('#nomEleve').text(`${prenom} ${nom}`);
                $("#informationEleve").text(`Elève en ${niveau} à ${etablissement}`)
                $("#matiere").text(matiere);
                $("#message").text(commentaire);
                $("#notification").text("Vous avez une demande de soutien en attente");
                $("#notification2").text("Utilisez le formulaire à gauche pour rejoindre le visio");
                $("#titleDemandeSoutien").removeClass("visually-hidden");
                $("#infosCoursEnAttente").removeClass("visually-hidden");

                $("#rejoindreVisio").click(function (e) {
                    $("#rejoindreVisio").prop("disabled", true);
                    $('#demandeEnAttente').empty();

                    // Set the new HTML content with an image and paragraph
                    var imageUrl = 'assets/img/products/1.jpg';
                    var imageHtml = '<img src="' + imageUrl + '" alt="Image Visio">';
                    var paragraphHtml = `<p class="text-success fw-bold">${prenom} ${nom}</p>`;

                    $('#demandeEnAttente').html(imageHtml + paragraphHtml);
                })
            }
        },
        error: function(){
            console.log("Y a un soucis quelque part bro...");
        }

    });
});

function capitalizeFirstLetter(str) {
    return str.charAt(0).toUpperCase() + str.slice(1);
}

function isJsonObjectEmpty(jsonObject) {
    for (var key in jsonObject) {
        if (jsonObject.hasOwnProperty(key)) {
            return false; // The object has at least one property, so it is not empty
        }
    }
    return true; // The object has no properties, indicating it is empty
}