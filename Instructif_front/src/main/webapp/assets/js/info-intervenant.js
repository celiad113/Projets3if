$(document).ready(function(){

    fillInfosIntervenant();

})

function fillInfosIntervenant(){
    return $.ajax({
        type: "GET",
        url: "action-servlet?todo=info-intervenant",
        dataType: "json",

        success: function(response){
            const intervenant = response.intervenant;

            updateInput($("#prenom"), intervenant.prenom);
            updateInput($("#nom"), intervenant.nom);
            updateInput($("#email"), intervenant.email);
            updateInput($("#numeroTel"), intervenant.telephone);
            updateInput($("#activite"), intervenant.activite);

            const niveaux = intervenant.niveaux;

            let select = $("#niveaux");

            niveaux.forEach(function (niveau){
                
                var option = $('<option></option>').val(niveau.id).html(niveau.nom);

                select.append(option);
            })

        },
        error : function(){
            console.log("Error in retrieving intervenant information");
        }
    })
}

function updateInput(input , value){
    $(input).removeAttr("readonly");
    $(input).val(value);
    $(input).attr("readonly", "readonly");
}