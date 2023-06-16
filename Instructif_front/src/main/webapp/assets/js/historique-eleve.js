$(document).ready(function(){

    $.ajax({
        type: "GET",
        url: "action-servlet?todo=historique-eleve",
        dataType: "json",

        success: function(response){
            var historique = response.historique;

            console.log(response);

            var tableBody = $("#tableBody");

            $.each(historique, function(index, cours){

                var date = cours.date;
                var note = cours.note;

                var enseignant = cours.enseignant;
                var prenom = enseignant.prenom;
                var nom = enseignant.nom;

                var matiere = cours.matiere;
                var nomMatiere = matiere.nomMatiere;

                var newRow = $("<tr>");
                newRow.append(`<td>${date}</td>`);
                newRow.append(`<td>${nomMatiere}</td>`);
                newRow.append(`<td>${note}/5</td>`);
                newRow.append(`<td>${prenom} ${nom}</td>`);

                tableBody.append(newRow);
            });

        },

        error: function(){
            console.log("Bon... c'est la merde");
        }
    })
})