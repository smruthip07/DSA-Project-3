<h1> README, Markdown, and Report Submission </h1>

For this project, you're expected to submit a report that is similar to those you've done for projects 1 and 2, with the proposal submitted in 3a included. To centralize this with your source code and video, you will write your Report in Markdown as a README file. Since you're supposed to create your project repository from this template, edit the existing README.md file, remove all the contents that are currently there, and replace them with your report.

Putting the README.md in your root or docs directory will automatically be recognized by GitHub and will be shown to anyone who visits the repository. For all documents, including README files, commit messages and issues, GitHub uses Markdown for formatting.

### Important Elements
|Element|Markdown Syntax| Example |
|-|-|-|
|Heading| # H1 <br> ## H2 <br> ### H3 <br> etc...| <h1>Heading 1</h1> <h2> Heading 2 </h2>  <h3> Heading 3 </h3>|
|Bold |	\*\*bold text** | **bold text** |
|Italic	|\*italicized text\*| *italics* |
|Blockquote	|> blockquote| <blockquote>blockquote</blockquote>
|Ordered List|1. First item <br> 2. Second item <br>3. Third item| <ol><li>First item</li><li>Second item</li><li>Third item</li></ol>
|Unordered List	| - First item <br> - Second item <br> - Third item|<ul><li>First item</li><li>Second item</li><li>Third item</li></ul>
|Code	|\`code`|`code`|
|Horizontal Rule	|---| <hr>|
|Link	|\[title](https://www.example.com)|[title](https://www.example.com)
|Image	|!\[alt text](image.jpg)|![alt text](images/image.jpg) |
Table	| \| Syntax \| Description \| <br> \| - \| - \| <br> \| Header \| Title \| <br> \| Paragraph \| Text \| | <table><tr><th>Syntax</th><th>Description</th></tr><tr><td>Header</td> <td>Title</td></tr><tr><td>Paragraph</td><td>Text</td></tr></table> |
Fenced Code Block	| \```<br>{<br>  "firstName": "John", <br>  "lastName": "Smith", <br>  "age": 25 <br>} <br> \``` | ![code](images/code.png) |
Footnote	| Here's a sentence with a footnote. [\^1] <br> [\^1]: This is the footnote.| Here's a sentence with a footnote. <sup style="font-size: smaller;">[[1]]()</sup> <br> 1. This is the footnote.

### Important Note on ToC

To include the Table of Contents (for your report), you can use links:

	\[link](www.example.com)

with the bulleted lists:

	- \[Section 1](#section-1)


If you have VS Code, it will then automatically add all headings into the table upon saving, but you first have to make it for all sections yourself. I would advise you to make it immediately in your report (or use the one in the [template report](REPORT.md)) and then it will update as you add more headings. If you want to exclude the title and table of contents as headings use the HTML heading syntax (\<h1>Heading 1\</h1>, \<h2>Heading 2\</h2>, \<h3>Heading 3\</h3>, ...)