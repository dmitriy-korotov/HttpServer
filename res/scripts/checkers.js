


/*
    FUNCTIONS
*/



function sleep(milliseconds) {
    const date = Date.now();
    let currentDate = null;
    do {
      currentDate = Date.now();
    } while (currentDate - date < milliseconds);
  }



function resizeDesk(desk)
{
    const FIELD_SIZE = window.innerWidth > window.innerHeight ? window.innerHeight : window.innerWidth;

    desk.setAttribute("style", `width: ${FIELD_SIZE}px;
                                height: ${FIELD_SIZE}px;
                                margin-top: ${((window.innerHeight - FIELD_SIZE) / 2)}px;
                                margin-left: ${((window.innerWidth - FIELD_SIZE) / 2)}px;`);
}



function clearSelections(field)
{
    let row_num = 0;
    field.forEach(row => {
        let ceil_num = 0;
        row.forEach(ceil => {
            ceil.classList.remove("selected");
            (row_num + ceil_num) % 2 ? ceil.classList.add("white") : ceil.classList.add("black");
            ++ceil_num;
        });
        ++row_num;
    });
}



function selectPathOverChakers(num_row, num_ceil, field, class_outher_checker, prev_move)
{
    if (0 <= num_row && num_row < field.length && 0 <= num_ceil && num_ceil < field[0].length && !field[num_row][num_ceil].hasChildNodes())
    {
        let this_elem = field[num_row][num_ceil];

        if (this_elem.classList.contains("selected"))
        {
            return;
        }

        this_elem.classList.add("selected");
        this_elem.classList.remove("white");

        // Right Bottom
        if (prev_move != DirectionMoves.LeftTop && 0 <= (num_row + 1) && (num_row + 1) < field.length && num_ceil + 1 < field[0].length)
        {
            let right_elem = field[num_row + 1][num_ceil + 1];
            if (right_elem.hasChildNodes() && right_elem.firstChild.classList.contains(class_outher_checker))
            {
                selectPathOverChakers(num_row + 2, num_ceil + 2, field, class_outher_checker, DirectionMoves.RightBottom);   
            }
        }
        // Left Bottom
        if (prev_move != DirectionMoves.RightTop && 0 <= (num_row + 1) && (num_row + 1) < field.length && num_ceil - 1 >= 0)
        {
            let left_elem = field[num_row + 1][num_ceil - 1];
            if (left_elem.hasChildNodes() && left_elem.firstChild.classList.contains(class_outher_checker))
            {
                selectPathOverChakers(num_row + 2, num_ceil - 2, field, class_outher_checker, DirectionMoves.LeftBottom);   
            }
        }
        // Right Top
        if (prev_move != DirectionMoves.LeftBottom && 0 <= (num_row - 1) && (num_row - 1) < field.length && num_ceil + 1 < field[0].length)
        {
            let right_elem = field[num_row - 1][num_ceil + 1];
            if (right_elem.hasChildNodes() && right_elem.firstChild.classList.contains(class_outher_checker))
            {
                selectPathOverChakers(num_row - 2, num_ceil + 2, field, class_outher_checker, DirectionMoves.RightTop);   
            }
        }
        // Left Top
        if (prev_move != DirectionMoves.RightBottom && 0 <= (num_row - 1) && (num_row - 1) < field.length && num_ceil - 1 >= 0)
        {
            let left_elem = field[num_row - 1][num_ceil - 1];
            if (left_elem.hasChildNodes() && left_elem.firstChild.classList.contains(class_outher_checker))
            {
                selectPathOverChakers(num_row - 2, num_ceil - 2, field, class_outher_checker, DirectionMoves.LeftTop);   
            }
        }
    }
}



function __selectKingChecker(num_row, num_ceil, field, vertical_step, horizintal_step, class_outher_checker, is_jumped_over_checker)
{
    if (0 <=  field[num_row][num_ceil].hasChildNodes())
    {
        
    }
}



function selectKingChecker(num_row, num_ceil, field, vertical_step, horizintal_step, class_outher_checker)
{
    __selectKingChecker(num_row, num_ceil, field, vertical_step, horizintal_step, class_outher_checker, false);
}



function selectChecker(num_row, num_ceil, field, vertical_step, class_outher_checker)
{
    let this_elem = field[num_row][num_ceil];

    this_elem.classList.add("selected");
    this_elem.classList.remove("white");

    // Right forward
    if (0 <= (num_row + vertical_step) && (num_row + vertical_step) < field.length && num_ceil + 1 < field[0].length)
    {
        let right_elem = field[num_row + vertical_step][num_ceil + 1];

        if (!right_elem.hasChildNodes())
        {
            right_elem.classList.add("selected");
            right_elem.classList.remove("white");
        }
        else if (right_elem.firstChild.classList.contains(class_outher_checker))
        {
            selectPathOverChakers(num_row + 2*vertical_step, num_ceil + 2, field, class_outher_checker,
                                  (vertical_step > 0) ? DirectionMoves.RightBottom : DirectionMoves.RightTop);
        }
    }
    // Left forward
    if (0 <= (num_row + vertical_step) && (num_row + vertical_step) < field.length && num_ceil - 1 >= 0)
    {
        let left_elem = field[num_row + vertical_step][num_ceil - 1];

        if (!left_elem.hasChildNodes())
        {
            left_elem.classList.add("selected");
            left_elem.classList.remove("white");
        }
        else if (left_elem.firstChild.classList.contains(class_outher_checker))
        {
            selectPathOverChakers(num_row + 2*vertical_step, num_ceil - 2, field, class_outher_checker,
                                  (vertical_step > 0) ? DirectionMoves.LeftBottom : DirectionMoves.LeftTop);
        }
    }

    let reverse_vertival_step = -vertical_step;

    // Right back
    if (0 <= (num_row + reverse_vertival_step) && (num_row + reverse_vertival_step) < field.length && num_ceil + 1 < field[0].length)
    {
        let right_elem = field[num_row + reverse_vertival_step][num_ceil + 1];

        if (right_elem.hasChildNodes() && right_elem.firstChild.classList.contains(class_outher_checker))
        {
            selectPathOverChakers(num_row + 2*reverse_vertival_step, num_ceil + 2, field, class_outher_checker,
                                  (reverse_vertival_step > 0) ? DirectionMoves.RightBottom : DirectionMoves.RightTop);
        }

    }
    // Left back
    if (0 <= (num_row + reverse_vertival_step) && (num_row + reverse_vertival_step) < field.length && num_ceil - 1 >= 0)
    {
        let left_elem = field[num_row + reverse_vertival_step][num_ceil - 1];

        if (left_elem.hasChildNodes() && left_elem.firstChild.classList.contains(class_outher_checker))
        {
            selectPathOverChakers(num_row + 2*reverse_vertival_step, num_ceil - 2, field, class_outher_checker,
                                  (reverse_vertival_step > 0) ? DirectionMoves.LeftBottom : DirectionMoves.LeftTop);
        }
    }
}



function selectPermitedSteps(checker, field)
{
    if (!checker.classList.contains(CURRENT_ACTIVE_CHECER))
    {
        return;
    }

    CURRENT_SELECTED_CHECKER = checker.parentElement;

    let div_index_in_ID = checker.parentElement.id.indexOf(';');
    let num_row = Number(checker.parentElement.id.substr(0, div_index_in_ID));
    let num_ceil = Number(checker.parentElement.id.substr(div_index_in_ID + 1, checker.parentElement.id.length));

    clearSelections(field);

    if (checker.classList.contains("black-checker-king"))
    {
        
    }  
    else if (checker.classList.contains("white-checker-king"))
    {
        
    }
    else if (checker.classList.contains("white-checker"))
    {
        selectChecker(num_row, num_ceil, field, -1, "white-checker");   
    }
    else if (checker.classList.contains("balck-checker"))
    {
        selectChecker(num_row, num_ceil, field, 1, "black-checker");   
    }
}



function getPathToSelectedElement(start, end, field, class_outher_checker, prev_checked)
{
    console.log(start, end);

    if (!start.classList.contains("selected"))
    {
        return [];
    }
    
    let div_index_in_ID = start.id.indexOf(';');
    let num_row_start = Number(start.id.substr(0, div_index_in_ID));
    let num_ceil_start = Number(start.id.substr(div_index_in_ID + 1, start.id.length));

    div_index_in_ID = end.id.indexOf(';');
    let num_row_end = Number(end.id.substr(0, div_index_in_ID));
    let num_ceil_end = Number(end.id.substr(div_index_in_ID + 1, end.id.length));

    if (start == end)
    {
        console.log("Finded!");
        return [[num_row_end, num_ceil_end]];
    }

    // Right bottom
    if (prev_checked != DirectionMoves.LeftTop && 0 <= (num_row_start + 1) && (num_row_start + 1) < field.length && num_ceil_start + 1 < field[0].length)
    {
        let right_elem = field[num_row_start + 1][num_ceil_start + 1];

        if (right_elem.hasChildNodes() && right_elem.firstChild.classList.contains(class_outher_checker)
            &&
            0 <= (num_row_start + 2) && (num_row_start + 2) < field.length && num_ceil_start + 2 < field[0].length)
        {
            let returned_path = getPathToSelectedElement(field[num_row_start + 2][num_ceil_start + 2], end, field, class_outher_checker, DirectionMoves.RightBottom);
            if (returned_path.length != 0)
            {
                return [].concat([[num_row_start, num_ceil_start]], returned_path);
            }
        }
    }
    // Left Bottom
    if (prev_checked != DirectionMoves.RightTop && 0 <= (num_row_start + 1) && (num_row_start + 1) < field.length && num_ceil_start - 1 >= 0)
    {
        let left_elem = field[num_row_start + 1][num_ceil_start - 1];
        
        if (left_elem.hasChildNodes() && left_elem.firstChild.classList.contains(class_outher_checker)
            &&
            0 <= (num_row_start + 2) && (num_row_start + 2) < field.length && num_ceil_start - 2 >= 0)
        {
            let returned_path = getPathToSelectedElement(field[num_row_start + 2][num_ceil_start - 2], end, field, class_outher_checker, DirectionMoves.LeftBottom);
            if (returned_path.length != 0)
            {
                return [].concat([[num_row_start, num_ceil_start]], returned_path);
            }   
        }
    }
    // Right Top
    if (prev_checked != DirectionMoves.LeftBottom && 0 <= (num_row_start - 1) && (num_row_start - 1) < field.length && num_ceil_start + 1 < field[0].length)
    {
        let right_elem = field[num_row_start - 1][num_ceil_start + 1];

        if (right_elem.hasChildNodes() && right_elem.firstChild.classList.contains(class_outher_checker)
            &&
            0 <= (num_row_start - 2) && (num_row_start - 2) < field.length && num_ceil_start + 2 < field[0].length)
        {
            let returned_path = getPathToSelectedElement(field[num_row_start - 2][num_ceil_start + 2], end, field, class_outher_checker, DirectionMoves.RightTop);
            if (returned_path.length != 0)
            {
                return [].concat([[num_row_start, num_ceil_start]], returned_path);
            }   
        }
    }
    // Left Top
    if (prev_checked != DirectionMoves.RightBottom && 0 <= (num_row_start - 1) && (num_row_start - 1) < field.length && num_ceil_start - 1 >= 0)
    {
        let left_elem = field[num_row_start - 1][num_ceil_start - 1];

        if (left_elem.hasChildNodes() && left_elem.firstChild.classList.contains(class_outher_checker)
            &&
            0 <= (num_row_start + 2) && (num_row_start - 2) < field.length && num_ceil_start - 2 >= 0)
        {
            let returned_path = getPathToSelectedElement(field[num_row_start - 2][num_ceil_start - 2], end, field, class_outher_checker, DirectionMoves.LeftTop);
            if (returned_path.length != 0)
            {
                return [].concat([[num_row_start, num_ceil_start]], returned_path);
            }   
        }
    }

    return [];
}



function beatTheCheckers(path, index_position, field)
{
    if (path.length < 2 || index_position + 1 >= path.length)
    {
        return;
    }
    let fst_index_beated_checker = (path[index_position][0] + path[index_position + 1][0]) / 2;
    let scnd_index_beated_checker = (path[index_position][1] + path[index_position + 1][1]) / 2;
    let beated_checker_parent = field[fst_index_beated_checker][scnd_index_beated_checker];

    let checker_position = field[path[index_position][0]][path[index_position][1]];
    let checker = checker_position.firstChild;
    checker_position.removeChild(checker_position.firstChild);

    beated_checker_parent.removeChild(beated_checker_parent.firstChild);
    
    field[path[index_position + 1][0]][path[index_position + 1][1]].appendChild(checker);

    setTimeout(() => { beatTheCheckers(path, index_position + 1, field); }, 500);
}



function moveIfForward(checker, target_position, field, vertical_step)
{
    let div_index_in_ID = checker.parentElement.id.indexOf(';');
    let num_row = Number(checker.parentElement.id.substr(0, div_index_in_ID));
    let num_ceil = Number(checker.parentElement.id.substr(div_index_in_ID + 1, checker.parentElement.id.length));

    if (0 <= (num_row + vertical_step) && (num_row + vertical_step) < field.length && num_ceil + 1 < field[0].length
        &&
        field[num_row + vertical_step][num_ceil + 1] == target_position)
    {
        let moved_checker = checker.cloneNode();
        checker.parentElement.removeChild(checker);
        moved_checker.addEventListener("click", () => { selectPermitedSteps(moved_checker, field); });
        target_position.appendChild(moved_checker);
        return true;
    }
    if (0 <= (num_row + vertical_step) && (num_row + vertical_step) < field.length && num_ceil - 1 >= 0
        &&
        field[num_row + vertical_step][num_ceil - 1] == target_position)
    {
        let moved_checker = checker.cloneNode();
        checker.parentElement.removeChild(checker);
        moved_checker.addEventListener("click", () => { selectPermitedSteps(moved_checker, field); });
        target_position.appendChild(moved_checker);
        return true;
    }
    return false;
}



function moveChecker(target_position)
{
    if (target_position.classList.contains("selected") && ! target_position.hasChildNodes())
    {
        CURRENT_ACTIVE_CHECER = (CURRENT_SELECTED_CHECKER.firstChild.classList.contains("white-checker") ? "black-checker" : "white-checker");

        var checker = CURRENT_SELECTED_CHECKER.firstChild;

        let premited_for_jump_checkers = (checker.classList.contains("white-checker")) ? "black-checker" : "white-checker";
        let vertical_step = (checker.classList.contains("white-checker")) ? -1 : 1;

        if (!moveIfForward(checker, target_position, field_array, vertical_step))
        {
            let path_to_selected_position = getPathToSelectedElement(CURRENT_SELECTED_CHECKER, target_position,
                                                                     field_array, premited_for_jump_checkers, DirectionMoves.NoMove);
            beatTheCheckers(path_to_selected_position, 0, field_array);
        }
        clearSelections(field_array);
    }
}



/*
    GLOBAL VARIABLES
*/



const FIELD_WIDTH = 8;
const FIELD_HEIGHT = 8;
const desk_ = document.getElementById("desk");
const field_ = document.getElementById("field");
const field_array = new Array();

const DirectionMoves = { LeftTop : 0, LeftBottom : 1, RightTop : 2, RightBottom : 3 , NoMove : 4 };

var CURRENT_SELECTED_CHECKER;
var CURRENT_ACTIVE_CHECER = "white-checker";


/*
    FIELD RENRED
*/



resizeDesk(desk_);
window.addEventListener("resize", () => { resizeDesk(desk_); }, false);



for (let i = 0; i < FIELD_HEIGHT; ++i)
{
    let row_ = document.createElement('div');
    row_.className = "row";

    let row_array = new Array();

    for (let j = 0; j < FIELD_WIDTH; ++j)
    {
        let ceil = document.createElement("div");
        ceil.className = "ceil " + ((i + j) % 2 ? "white" : "black");
        ceil.id = i + ";" + j;
        ceil.addEventListener("click", () => { moveChecker(ceil); }, false);

        if (i < 3 && (i + j) % 2 == 1)
        {
            let checker = document.createElement("div");
            checker.className = "checker black-checker";
            checker.addEventListener("click", () => { selectPermitedSteps(checker, field_array) }, false);
            ceil.appendChild(checker);
        }
        if (i > 4 && (i + j) % 2 == 1)
        {
            let checker = document.createElement("div");
            checker.className = "checker white-checker";
            checker.addEventListener("click", () => { selectPermitedSteps(checker, field_array) }, false);
            ceil.appendChild(checker);
        }
        
        row_array.push(ceil);
        row_.appendChild(ceil);
    }
    field_array.push(row_array);
    field_.appendChild(row_);
}