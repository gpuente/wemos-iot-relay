var inline = require('gulp-inline')
  , uglify = require('gulp-uglify')
  , minifyCss = require('gulp-minify-css')
  , gulp = require('gulp')
  , htmlmin = require('gulp-htmlmin')
  , replace = require('gulp-replace');
  
  gulp.task('default', function(){
    return gulp.src(['src/index.html', 'src/panel.html'])
        .pipe(inline({
            base: 'src/',
            js: uglify,
            css: [minifyCss]
        }))
        .pipe(htmlmin({ collapseWhitespace: true }))
        .pipe(replace('"', '\\"'))
        .pipe(gulp.dest('dist/'));
  });