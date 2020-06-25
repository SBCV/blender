
.. Keep this document short & concise,
   linking to external resources instead of including content in-line.
   See 'release/text/readme.html' for the end user read-me.


Blender for Satellite Reconstruction Visualization
==================================================


Prequisites:
-----------

- Clone this repository <path/to/blender-github>
- replace the content of <blender-github/.git/config> with <blender-github/corrected_git_config>

	i.e. replace the URLS
		url = https://github.com/SBCV/blender-translations.git
		url = https://github.com/SBCV/blender-addons.git
		url = https://github.com/SBCV/blender-addons-contrib.git
		url = https://github.com/SBCV/blender-dev-tools.git
	with
		url = https://git.blender.org/blender-translations.git
		url = https://git.blender.org/blender-addons.git
		url = https://git.blender.org/blender-addons-contrib.git
		url = https://git.blender.org/blender-dev-tools.git


Development
-----------

- `Build Instructions <https://wiki.blender.org/wiki/Building_Blender>`__
- `Code Review & Bug Tracker <https://developer.blender.org>`__
- `Developer Forum <https://devtalk.blender.org>`__
- `Developer Documentation <https://wiki.blender.org>`__


License
-------

Blender as a whole is licensed under the GNU Public License, Version 3.
Individual files may have a different, but compatible license.

See `blender.org/about/license <https://www.blender.org/about/license>`__ for details.



Changes
-------
set "RNA_def_property_range(prop, -100000.0f, 100000.0f);" of shift_x and shift_y in 
	blender/source/blender/makesrna/intern/rna_camera.c

set clip_end = 1000000.0f in
	blender/source/blender/makesdna/DNA_camera_defaults.h

set clip_end = 1000000.0f in
	blender/source/blender/makesdna/DNA_view3d_defaults.h


