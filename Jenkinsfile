pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        parallel(
          "Build": {
            sh './setup.sh'
            sh 'cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang .'
          },
          "Documentation": {
            sh 'doxygen ./doxygen-config'
            sh 'zip -r docs.zip docs'
          }
        )
      }
    }
  }
}