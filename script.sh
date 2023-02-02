#!/bin/bash

function dataCollec(){
    local -a tab=("${!1}")
    local length=${#tab[@]}
    local -a dataType=("-t1" "-t2" "-t3" "-p1" "-p2" "-p3" "-w" "-h" "-m")
    local -a tab_data=()

    for ((i=0; i<$length; i++)); do
        for data in ${dataType[*]}; do
            if [ "$data" = "${tab[$i]}" ]; then
                tab_data+=(${tab[$i]})
            fi
        done
    done

    echo ${tab_data[@]}
}
function sortCollec(){
    local -a tab=("${!1}")
    local length=${#tab[@]}
    local -a sortType=("--list" "--abr" "--avl")
    local sort="--avl"  #AVL is the default choice if the user doesn't choose a specific sort

    for ((i=0; i<$length; i++)); do
        for sorts in ${sortType[*]}; do
            if [ "$sorts" = "${tab[$i]}" ]; then
                sort=(${tab[$i]})
            fi
        done
    done

    echo $sort
}
function regionCollec(){
    local -a tab=("${!1}")
    local length=${#tab[@]}
    local -a locType=("-F" "-G" "-S" "-A" "-Q" "-O")
    local region="ALL"  #Specific region argument isn't necessary to run the program

    for ((i=0; i<$length; i++)); do
        for loca in ${locType[*]}; do
            if [ "$loca" = "${tab[$i]}" ]; then
                region=(${tab[$i]})
            fi
        done
    done

    echo $region
}
function fileCollec(){
    local -a tab=("${!1}")
    local length=${#tab[@]}
    local file=''

    for ((i=0; i<$length; i++)); do
        if echo "${tab[$i]}" | grep -q ".csv"; then
            file=(${tab[$i]})
        fi
    done

    echo $file
}
function argVerif() {
    local -a tab=("${!1}")
    local length=${#tab[@]}
    local -a dataType=("-t1" "-t2" "-t3" "-p1" "-p2" "-p3" "-w" "-h" "-m")
    local -a locType=("-F" "-G" "-S" "-A" "-Q" "-O")
    local -a sortType=("--list" "--abr" "--avl")
    nbType=0
    nbLoc=0
    nbSort=0
    file=0

    for ((i=0; i<$length; i++)); do
    #vérification des données entrées
        for data in ${dataType[*]}; do
            if [ "${tab[$i]}" = "$data" ]; then
                nbType=$(($nbType+1))
            fi
        done
    #vérification de la localisation saisie
        for loca in ${locType[*]}; do
            if [ "${tab[$i]}" = "$loca" ]; then
                nbLoc=$(($nbLoc+1))
            fi
        done
    #vérification du type de tri demandé
        for sort in ${sortType[*]}; do
            if [ "${tab[$i]}" = "$sort" ]; then
                nbSort=$(($nbSort+1))
            fi
        done
    #vérification de la bonne entrée du fichier csv
        if [ "${tab[i]}" = "-f" ]; then
            if ! file -i "${tab[$(($i+1))]}" | grep -q '.csv'; then
                echo "ERROR: missing csv file Syntax should be : -f file.csv"
                exit 1
            else
                file=1
            fi 
        fi
    done

    #Affichage du message d'erreur correspondant
    if [ $file -eq 0 ]; then
        echo "ERROR: missing csv file argument"
        exit 1
    fi
    if [ $nbType -eq 0 ]; then
        echo "ERROR: missing data argument(s)"
        exit 1
    fi
    if [ $nbSort -gt 1 ]; then
        echo "ERROR: too much sort arguments"
        exit 1
    fi
    if [ $nbLoc -gt 1 ]; then
        echo "ERROR: too much localization arguments"
        exit 1
    fi
    if [ $nbSort -gt 1 ]; then
        echo "ERROR: too much sort arguments"
        exit 1
    fi
}

argTab=("$@")
argVerif argTab[@]

#Arguments collection
dataTab=($(dataCollec argTab[@]))
sort=$(sortCollec argTab[@])
region=$(regionCollec argTab[@])
dataFile=$(fileCollec argTab[@])

#User can choose several data arguments (like -t3 and -w for instance), we have to run the program for each data argument
for data in ${dataTab[*]}; do
    opt1=1
    opt2=2
    if [ "$data" = "-t1" ] || [ "$data" = "-t2" ] || [ "$data" = "-t3" ]; then
        opt3=12
    elif [ "$data" = "-p1" ] || [ "$data" = "-p2" ] || [ "$data" = "-p3" ]; then
        opt3=7
    elif [ "$data" = "-h" ]; then
        opt3=15
    elif [ "$data" = "-m" ]; then
        opt3=6
    else
        opt3=4
        opt4=5
    fi

    #Extracting corresponding lines and columns in dataFile
    if [ "$region" = "ALL" ]; then
        #No region selected
        if [ "$data" = "-w" ]; then
            awk -F, -v a=$opt1 -v b=$opt2 -v c=$opt3 -v d=$opt4 '{print $a ";" $b ";" $c ";" $d}' $dataFile > temp.csv
        else
            awk -F, -v a=$opt1 -v b=$opt2 -v c=$opt3 '{print $a ";" $b ";" $c}' $dataFile > temp.csv
            if [ "$data" = "-t3" ] || [ "$data" = "-p3" ]; then
                sort -t, -k1,1 -n temp.csv > temp2.csv && mv temp2.csv temp.csv
            fi
        fi

    elif [ "$region" = "-F" ]; then
        #France selected
        if [ "$data" = "-w" ]; then
            awk -F, -v a=$opt1 -v b=$opt2 -v c=$opt3 -v d=$opt4 '$16 < 96000 {print $a ";" $b ";" $c ";" $d}' $dataFile > temp.csv
        else
            awk -F, -v a=$opt1 -v b=$opt2 -v c=$opt3 '$16 < 96000 {print $a ";" $b ";" $c}' $dataFile > temp.csv
            if [ "$data" = "-t3" ] || [ "$data" = "-p3" ]; then
                sort -t, -k1,1 -n temp.csv > temp2.csv && mv temp2.csv temp.csv
            fi
        fi

    elif [ "$region" = "-G" ]; then
        #Guyane selected
        if [ "$data" = "-w" ]; then
            awk -F, -v a=$opt1 -v b=$opt2 -v c=$opt3 -v d=$opt4 '$16 >= 97301 && $16 <= 97362 {print $a ";" $b ";" $c ";" $d}' $dataFile > temp.csv
        else
            awk -F, -v a=$opt1 -v b=$opt2 -v c=$opt3 '$16 >= 97301 && $16 <= 97362 {print $a ";" $b ";" $c}' $dataFile > temp.csv
            if [ "$data" = "-t3" ] || [ "$data" = "-p3" ]; then
                sort -t, -k1,1 -n temp.csv > temp2.csv && mv temp2.csv temp.csv
            fi
        fi

    elif [ "$region" = "-S" ]; then
        #Saint Pierre et Miquelon selected
        if [ "$data" = "-w" ]; then
            awk -F, -v a=$opt1 -v b=$opt2 -v c=$opt3 -v d=$opt4 '$10 == 46.766333 && $11 == -56.179167 {print $a ";" $b ";" $c ";" $d}' $dataFile > temp.csv
        else
            awk -F, -v a=$opt1 -v b=$opt2 -v c=$opt3 '$10 == 46.766333 && $11 == -56.179167 {print $a ";" $b ";" $c}' $dataFile > temp.csv
            if [ "$data" = "-t3" ] || [ "$data" = "-p3" ]; then
                sort -t, -k1,1 -n temp.csv > temp2.csv && mv temp2.csv temp.csv
            fi
        fi

    elif [ "$region" = "-A" ]; then
        #Antilles selected
        if [ "$data" = "-w" ]; then
            awk -F, -v a=$opt1 -v b=$opt2 -v c=$opt3 -v d=$opt4 '$16 >= 97201 && $16 <= 97232 {print $a ";" $b ";" $c ";" $d}' $dataFile > temp.csv
        else
            awk -F, -v a=$opt1 -v b=$opt2 -v c=$opt3 '$16 >= 97201 && $16 <= 97232 {print $a ";" $b ";" $c}' $dataFile > temp.csv
            if [ "$data" = "-t3" ] || [ "$data" = "-p3" ]; then
                sort -t, -k1,1 -n temp.csv > temp2.csv && mv temp2.csv temp.csv
            fi
        fi

    elif [ "$region" = "-O" ]; then
        #Indian Ocean selected
        if [ "$data" = "-w" ]; then
            awk -F, -v a=$opt1 -v b=$opt2 -v c=$opt3 -v d=$opt4 '$10 >= -49.352333 && $10 <= -15.887667 && $11 <= 77.569167 && $11 >= 40.340667 {print $a ";" $b ";" $c ";" $d}' $dataFile > temp.csv
        else
            awk -F, -v a=$opt1 -v b=$opt2 -v c=$opt3 '$10 >= -49.352333 && $10 <= -15.887667 && $11 <= 77.569167 && $11 >= 40.340667 {print $a ";" $b ";" $c}' $dataFile > temp.csv
            if [ "$data" = "-t3" ] || [ "$data" = "-p3" ]; then
                sort -t, -k1,1 -n temp.csv > temp2.csv && mv temp2.csv temp.csv
            fi
        fi
    else 
        #Antarctic selected
        if [ "$data" = "-w" ]; then
            awk -F, -v a=$opt1 -v b=$opt2 -v c=$opt3 -v d=$opt4 '$16 >= 97501 && $16 <= 97502 {print $a ";" $b ";" $c ";" $d}' $dataFile > temp.csv
        else
            awk -F, -v a=$opt1 -v b=$opt2 -v c=$opt3 '$16 >= 97501 && $16 <= 97502 {print $a ";" $b ";" $c}' $dataFile > temp.csv
            if [ "$data" = "-t3" ] || [ "$data" = "-p3" ]; then
                sort -t, -k1,1 -n temp.csv > temp2.csv && mv temp2.csv temp.csv
            fi
        fi
    fi

    #Collecting number of line for the C program
    nbLine=$(wc -l temp.csv | awk '{print $1}')

    #Executing C program
    if [ ! -e "exec" ]; then
        make
    fi
    ./exec $data temp.csv $sort $nbLine
done