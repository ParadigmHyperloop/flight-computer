pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        parallel(
          "Build": {
            sh './setup.sh'
            sh 'rm -rf build && mkdir -p build'
            sh 'cd build && ls -lah'
            sh 'cd build && cmake ..'
            sh 'cd build && ls -lah'
            sh 'cd build && pwd'
            sh 'cd build && make'
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
         sh 'cd build && make check'
      }
    }
  }
  post {
    always {
      archive 'docs.zip'
    }
  }
}