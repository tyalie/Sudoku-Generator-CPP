# Sudoku Generator in C++
This Sudoku Generator is an application programmed in C++ and the help of QT5. 
The algorithmic is based on the paper <a href="http://zhangroup.aporc.org/images/files/Paper_3485.pdf">Sudoku Puzzles Generating: from Easy to Evil</a> and the underlying cmake folder structure was provided by <a href="https://github.com/euler0/mini-cmake-qt">mini-cmake-qt</a> (I gave up on doing it by myself).
The program code is in parts equal to my previous project <a href="https://github.com/Gansgar/Sudoku-Generator">Sudoku Generator</a>. This project now is fundamentaly the same, but uses the supperior features of C++11 over Java and Qt5 over Swing.

## Features

<p>The features of the this project are extending the feature list of the Java implementation by introducing stack generation for OpenSudoku and a larger amount of available export formats (like *.png, *.jpg, *.svg, …).</p>

<p>
Most features are listed below:
<ul>
    <li>Sudoku Generation on various difficulties</li>
    <li>Sudoku Solving</li>
    <li>Live sudoku validation</li>
    <li>Fast sudoku type in</li>
    <li>Saving the current sudoku</li>
    <li>Stackgeneration of sudokus in <i>OpenSudoku</i> format</li>
</ul>
</p>

## <i><a href="http://opensudoku.moire.org">OpenSudoku</a></i> support
<b><i>OpenSudoku</i> Support only means export of sudokus. There's no import feature in this application</b>
<p>
<i>OpenSudoku</i> provides an import feature for new sudokus. The feature is constructed in such a way that sudokus can only be imported as a folder, that will include multiple puzzles. Sudoku Generator makes use of that and allows to generate sudokus in a self definded stack-size with a selected difficulty in exactly the by OpenSudoku used format. The generation process is multithreaded to provide a fast generation of even thousands of sudokus an acceptable time.
</p>
<p>
In the <i>OpenSudoku</i> app just go into the context menu and click import. In the appearing file chooser select the generated sudoku file (use USB, Dropbox or Co to move file from computer to your phone) and enjoy the new sudokus.
</p>

## Compile
To compile this app on your own  you need to install Qt 5.6 and need to set the CMAKE_PREFIX_PATH in the CMakeLists.txt to your QT installation directory. 
