$(document).ready(function(){

    fillInfosEleve();

})

function fillInfosEleve(){
    return $.ajax({
        type : "GET",
        url : "action-servlet?todo=info-eleve",
        dataType: "json",

        success: function(response){

            const eleve = response.eleve;

            updateInput($("#prenom") , eleve.prenom);
            updateInput($("#nom"), eleve.nom);
            updateInput($("#email"), eleve.username);
            updateInput($("#dateDeNaissance"), eleve.dateNaissance);

            const etablissement = eleve.etablissement;

            updateInput($("#codeEtablissement"), etablissement.code);

            const niveau = eleve.niveau;

            updateInput($("#niveau"), niveau.nom);
        },
        error: function(){
            console.log("An error happened.");
        }
    })
}

function updateInput(input , value){
    $(input).removeAttr("readonly");
    $(input).val(value);
    $(input).attr("readonly", "readonly");
}