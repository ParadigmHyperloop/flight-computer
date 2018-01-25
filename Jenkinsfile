pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        parallel(
          "Build": {
            sh './setup.sh'
            sh 'cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang .'
            sh 'make'
          },
          "Documentation": {
            sh 'doxygen ./doxygen-config'
            sh 'zip -r docs.zip docs'
          }
        )
      }
    }
    stage('Test') {
      steps {
         sh 'make check'
      }
    }
  }
  post {
    always {
      archive 'docs.zip'
    }
  }
}