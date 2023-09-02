<h1>Minesweeper</h1>

<p>A Minesweeper game implementation using SFML.</p>

<h2>Table of Contents</h2>
<ul>
  <li><a href="#prerequisites">Prerequisites</a></li>
  <li><a href="#installation">Installation</a></li>
  <li><a href="#compilation">Compilation</a></li>
  <li><a href="#running-the-program">Running the Program</a></li>
  <li><a href="#license">License</a></li>
</ul>

<h2 id="prerequisites">Prerequisites</h2>

<p>Before you begin, ensure you have met the following requirements:</p>
<ul>
  <li>A C++ compiler with support for C++17.</li>
  <li><a href="https://www.sfml-dev.org/">SFML (Simple and Fast Multimedia Library)</a></li>
</ul>

<h2 id="installation">Installation</h2>

<h3>Installing SFML</h3>

<p>Depending on your platform, the installation process might vary:</p>

<ul>
  <li><strong>Debian/Ubuntu</strong>:
    <pre>sudo apt-get install libsfml-dev</pre>
  </li>
  <li><strong>Fedora</strong>:
    <pre>sudo dnf install SFML</pre>
  </li>
  <li><strong>Arch Linux</strong>:
    <pre>sudo pacman -S sfml</pre>
  </li>
  <li><strong>macOS (using Homebrew)</strong>:
    <pre>brew install sfml</pre>
  </li>
  <li><strong>Windows</strong>: Download the SFML SDK from the <a href="https://www.sfml-dev.org/download.php">official website</a> and set it up with your preferred IDE.</li>
</ul>

<h2 id="compilation">Compilation</h2>

<p>To compile the Minesweeper game, use the following commands:</p>

<ul>
  <li>For the main program (<code>Project 3 Minesweeper.cpp</code>):
    <pre>g++ -std=c++17 "Project 3 Minesweeper.cpp" -o minesweeper -lsfml-graphics -lsfml-window -lsfml-system</pre>
  </li>
  <li>For <code>TextureManager.cpp</code>:
    <pre>g++ -std=c++17 "TextureManager.cpp" -o texture_manager -lsfml-graphics -lsfml-window -lsfml-system</pre>
  </li>
  <li>For <code>Tile.cpp</code>:
    <pre>g++ -std=c++17 "Tile.cpp" -o tile -lsfml-graphics -lsfml-window -lsfml-system</pre>
  </li>
</ul>

<h2 id="running-the-program">Running the Program</h2>

<p>After compilation, you can run the Minesweeper game using the following command:</p>

<pre>./minesweeper</pre>

<h2 id="license">License</h2>

<p>This project uses the following license: <a href="#link-to-license">License Name</a>.</p>
