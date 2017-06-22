# The Hammer 3.0
Next version of the source code editor The Hammer 3. Completely renovated.

=== Get the Hammer 3.0 preview ===

For CVS Users: You can find it here:
http://projects.vdf-guidance.com/projects/hammer/files 

Download the file that has a filename like:
Hammer3-development-snapshot-2017mmdd.zip
where mm=month and dd=day of the date we created the snapshot of our development files.

For now the preview is not considered stable and could be used to look at and play with.

In there you'll find a workspace that can let you build Hammer3.

If you want to compile Hammer 3.0 then use one of the Hammer3.xx.sws workspace files.
You should select Hammer3.src to compile.
You can use Hammer3-182.src to compile for DF18.2, Hammer3-190.src to compile for DF19.0 etcetera.
The lowest supported version of DataFlex that you can use to compile it with is DF18.1.

DataFlex: http://www.dataaccess.com

The Hammer itself however is made to work with ALL versions of DataFlex, we just don't want to have to miss out on all the great
improvements in DataFlex for our development on the Hammer itself.

The codemax control is also planned to be removed in a later stage, once migration is a success.
For now it will be there.

=== Get the Hammer via Subversion ===

In order to check out a working copy of The Hammer 3.0 need to add some files that are not versioned. These are mainly binary files that are subject to change. Files we do not even want under version control as they would cause too much noise.

There are two versions of binary files addons that are required for your runtime environment.
The files are also stored in Subversion, but directly under the trunk folder.

For VDF18.1 and up:
http://svn.vdf-guidance.com/TheHammer/trunk/Hammer-vdf12-dependencies.zip

So go get the one you need if you missed checking them out already.

You should unzip the Hammer-xxx-dependencies file of your choice over the existing folder.

The Hammer will not run without those data files!

--
Hammer time
Team
