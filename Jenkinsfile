pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        parallel(
          "Build": {
            sh './setup.sh'
            sh 'mkdir -p build'
            sh 'cd build && ls -lah'
            sh 'cd build && cmake -D CMAKE_CXX_COMPILER=/usr/bin/clang -D CMAKE_C_COMPILER=/usr/bin/clang ..'
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